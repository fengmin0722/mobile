#ifndef __TAF_LOGGER_H__
#define __TAF_LOGGER_H__

#include "util/tc_logger.h"
#include "util/tc_file.h"
#include "util/tc_singleton.h"
#include "servant/Global.h"
#include "log/Log.h"

#define DYEING_DIR "taf_dyeing"
#define DYEING_FILE "dyeing"

namespace taf
{

/**
 * LOG的库说明:
 * 用例请看test/log的代码
 * 1 循环日志采用LOG->error(), LOG->debug()
 * 2 循环日志不上传到服务器
 * 3 按天日志采用DLOG, FDLOG来记录
 * 4 按天日志也可以不上传到远程服务器:DLOG("")->disableRemote();
 * 5 按天日志可以改变每天一个文件的方式:
 *   DLOG("abc3")->setFormat("%Y%m%d%H");
 *   每个小时一个文件
 */

/*****************************************************************************
实现方式说明(只介绍按时间的日志, 会写到taflog):
    1 自定义时间日志的WriteT类:RemoteTimeWriteT
    2 在RemoteTimeWriteT类中, 写入到远程
    3 定义远程日志类:typedef TC_Logger<RemoteTimeWriteT, TC_RollByTime> RemoteTimeLogger;
    4 为了保证远程的写日志也是在单独线程处理,重新定义本地按天日志类
    5 自定义时间日志的WriteT类:TimeWriteT
    6 在TimeWriteT类中包含RemoteTimeLogger对象
    7 在TimeWriteT类的写入操作中, 写入本地文件后, 同时写入到RemoteTimeLogger对象中
    8 RemoteTimeLogger会在RemoteTimeWriteT对象中, 异步写入到远程
    9 从而本地文件写和远程写不在一个线程中.
*****************************************************************************/

///////////////////////////////////////////////////////////////////////////////

class RollWriteT
{
public:
    RollWriteT();
    ~RollWriteT();

    void operator()(ostream &of, const deque<pair<int, string> > &ds);

    void setDyeingLogInfo(const string &sApp, const string &sServer, const string & sLogPath,
            int iMaxSize, int iMaxNum, const CommunicatorPtr &comm, const string & sLogObj);

protected:

    TC_RollLogger *_pDyeingRollLogger;

    static int  _iDyeingThread;

    string _sApp;
    string _sServer;
    string _sLogPath;
    int _iMaxSize;
    int _iMaxNum;

    /**
     * 染色远程滚动日志代理
     */
    LogPrx                _logPrx;


};


/**
 * 本地日志帮助类, 单件
 * 循环日志单件是永生不死的, 保证任何地方都可以使用
 * 当该对象析够以后, 则直接cout出来
 */
class TafRollLogger : public TC_Singleton<TafRollLogger, CreateUsingNew, PhoneixLifetime>
{
public:
		enum
		{
			NONE_LOG    = 1,	/**所有的log都不写*/
			ERROR_LOG   = 2,	/**写错误log*/
			WARN_LOG    = 3,	/**写错误,警告log*/
			DEBUG_LOG   = 4,	/**写错误,警告,调试log*/
			INFO_LOG    = 5		/**写错误,警告,调试,Info log*/
		};
public:
    typedef TC_Logger<RollWriteT, TC_RollBySize> RollLogger;

    /**
     * 设置本地信息
     * @param app, 业务名称
     * @param server, 服务名称
     * @param logpath, 日志路径
     * @param iMaxSize, 文件最大大小,字节
     * @param iMaxNum, 文件最大数
     */
    void setLogInfo(const string &sApp, const string &sServer, const string &sLogpath, int iMaxSize = 1024*1024*50, int iMaxNum = 10, const CommunicatorPtr &comm=NULL, const string &sLogObj="");

    /**
     * 设置同步写日志
     *
     * @param bSync
     */
    void sync(bool bSync = true);

    /**
     * 获取循环日志
     *
     * @return RollLogger
     */
    RollLogger *logger()          { return &_logger; }

    /**
     * 染色日志是否启用
     * @param bEnable
     */
    void enableDyeing(bool bEnable, const string& sDyeingKey = "");

protected:

    /**
     * 应用
     */
    string                  _sApp;

    /**
     * 服务名称
     */
    string                  _sServer;

    /**
     * 日志路径
     */
    string                  _sLogpath;

    /**
     * 循环日志
     */
    RollLogger           _logger;

    /**
     * 本地线程组
     */
    TC_LoggerThreadGroup    _local;

};

///////////////////////////////////////////////////////////////////////////////////////
//
/**
 * 写日志线程
 * 将写本地日志和远程分开到不同的线程
 * 作为单件存在, 且是永生不死的单件
 */
class TafLoggerThread : public TC_Singleton<TafLoggerThread, CreateUsingNew, PhoneixLifetime>
{
public:
    /**
     * 构造函数
     */
    TafLoggerThread();

    /**
     * 析够函数
     */
    ~TafLoggerThread();

    /**
     * 本地写日志线程
     */
    TC_LoggerThreadGroup* local();

    /**
     * 远程写日志线程
     *
     * @return TC_LoggerThreadGroup*
     */
    TC_LoggerThreadGroup* remote();

protected:

    /**
     * 本地线程组
     */
    TC_LoggerThreadGroup    _local;

    /**
     * 远程写线程组
     */
    TC_LoggerThreadGroup    _remote;
};

///////////////////////////////////////////////////////////////////////////////////////
class TimeWriteT;

/**
 * 远程的Log写操作类
 */
class RemoteTimeWriteT
{
public:
    ~RemoteTimeWriteT();

    /**
     * 构造函数
     */
    void setTimeWriteT(TimeWriteT *pTimeWrite);

    /**
     * 具体调用
     * @param of
     * @param buffer
     */
    void operator()(ostream &of, const deque<pair<int, string> > &buffer);

protected:
    /**
     * 同步到远程
     */
    void sync2remote(const vector<string> &buffer);

    /**
     * 染色日志同步到远程
     */
    void sync2remoteDyeing(const vector<string> &buffer);

protected:
    /**
     * 指针
     */
    TimeWriteT          *_pTimeWrite;

};

////////////////////////////////////////////////////////////////////////////
/**
 * 写Logger
 */
class TimeWriteT
{
public:
    typedef TC_Logger<RemoteTimeWriteT, TC_RollByTime> RemoteTimeLogger;

    typedef TC_Logger<TC_DefaultWriteT, TC_RollByTime> DyeingTimeLogger;

    /**
     * 构造
     */
    TimeWriteT();

    /**
     * 析够
     */
    ~TimeWriteT();

    /**
     * 设置基本信息
     * @param app, 应用名称
     * @param server, 服务名称
     * @param file, 日志文件名
     * @param sFormat, 格式
     */
    void setLogInfo(const LogPrx &logPrx, const string &sApp, const string &sServer, const string &sFile, const string &sLogpath, const string &sFormat,const string& setdivision="");

    /**
     * 设置代理
     * @param logPrx 代理信息
     */
    void setLogPrx(const LogPrx &logPrx);

    /**
     * 远程日志功能打开或关闭
     * @param bEnable
     */
    void enableRemote(bool bEnable)         { _bRemote = bEnable; }

    /**
     * 本地日志功能功能打开或关闭
     * @param bEnable
     */
    void enableLocal(bool bEnable);

    /**
     * 染色日志功能打开或关闭
     * @param bEnable
     */
    void enableDyeing (bool bEnable, const string& sDyeingKey = "");


	/**
	 * @brief 日志文件名是否带.log后缀
	 * @param bEnable
	 */
	void enableSufix(bool bEnable=true){_bHasSufix = bEnable;}
	/**
	 * @brief 是否允许框架在日志文件名上增加业务相关的标识
	 * @param bEnable
	 */
	void enablePrefix(bool bEnable=true){_bHasAppNamePrefix = bEnable;}
	/**
	 * @brief 日志文件名中用户自定义字符与日期字符间的连接符，默认是"_"
	 * @param str
	 */
	void setFileNameConcatStr(const string& str) {_sConcatStr = str;}

	/**
	 * @brief 框架中增加的日志内容之间的分割符，默认是"|"
	 * @param str
	 */
	void setSeparator(const string& str) {_sSepar = str;}

	/**
	 * @brief 框架中日期和时间之间是否需要加中括号[],有些统计由特殊需求；默认不加
	 * @param bEnable
	 */
	void enableSqareWrapper(bool bEnable) {_bHasSquareBracket = bEnable;}


    /**
     * 设置时间格式("%Y%m%d")
     * @param sFormat
     */
    void setFormat(const string &sFormat)   { _sFormat = sFormat; }

    /**
     * 具体调用
     * @param of
     * @param buffer
     */
    void operator()(ostream &of, const deque<pair<int, string> > &buffer);

protected:

    /**
     * 友元
     */
    friend class RemoteTimeWriteT;

    /**
     * 记录错误文件
     * @param buffer
     */
    void writeError(const vector<string> &buffer);

    /**
     * 记录错误文件
     * @param buffer
     */
    void writeError(const deque<pair<int, string> > &buffer);

    /**
     * 初始化logger
     */
    void initError();

    /**
     * 初始化染色日志
     */
    void initDyeingLog();

protected:

    /**
     * 远程时间日志
     */
    RemoteTimeLogger    *_pRemoteTimeLogger;

    /**
     * 远程功能
     */
    bool                _bLocal;

    /**
     * 远程功能
     */
    bool                _bRemote;

    /**
     * 远程服务句柄
     */
    LogPrx              _logPrx;

    /**
     * app名称
     */
    string              _sApp;

    /**
     * 服务名称
     */
    string              _sServer;

    /**
     * 日志文件名称
     */
    string              _sFile;

    /**
     * 时间格式
     */
    string              _sFormat;

    /**
     * 具体文件
     */
    string              _sFilePath;

    /**
     * 错误文件
     */
    TC_DayLogger        _elogger;

    /**
     * 缺省写模式
     */
    TC_DefaultWriteT    _wt;

    /**
     * 染色日志
     */
    static int                _bDyeing;

    /**
     * 染色日志目录路径
     */
    string              _sDyeingFilePath;

    /**
     * 远程时间日志
     */
    DyeingTimeLogger    *_pDyeingTimeLogger;

    /**
     * set分组信息
     */
    string                  _sSetDivision;

	/**
	 * 日志文件名是否带.log后缀
	 */
	bool					_bHasSufix;
	/**
	 * 是否允许框架在日志文件名上增加业务相关的标识
	 */
	bool 					_bHasAppNamePrefix;

	/**
	 * 日志文件名中用户自定义字符与日期字符间的连接符，默认是"_"
	 */
	string 					_sConcatStr;
	/**
	 * 分隔符
	 */
	 string        _sSepar;
	/**
	 * 日期部分是否加上[]
	 */
	 bool 		  _bHasSquareBracket;
};

////////////////////////////////////////////////////////////////////////////

/**
 * 远程日志帮助类, 单件
 */
class TafTimeLogger : public TC_HandleBase
                    , public TC_ThreadLock
                    , public TC_Singleton<TafTimeLogger, CreateUsingNew, DefaultLifetime>
{
public:

    //定义按时间滚动的日志
    typedef TC_Logger<TimeWriteT, TC_RollByTime> TimeLogger;

    /**
     * 构造
     */
    TafTimeLogger();

    /**
     * 析够
     */
    ~TafTimeLogger();

    /**
     * 设置本地信息
     * @param comm, 通信器
     * @param obj, 日志对象名称
     * @param app, 业务名称
     * @param server, 服务名称
     * @param logpath, 日志路径
     */
    void setLogInfo(const CommunicatorPtr &comm, const string &obj, const string &sApp, const string &sServer, const string &sLogpath,const string& setdivision="");

    /**
     * 初始化设置时间格式("%Y%m%d")
     * 不要动态修改, 线程不安全
     * 如果有需要, 初始化后直接修改
     * @param sFormat, 文件名称, 为空表示缺省的时间日志
     */
    void initFormat(const string &sFile, const string &sFormat);

    /**
     * 获取时间日志
     * @param file
     */
    TimeLogger *logger(const string &sFile = "");

    /**
     * 获取时间日志
     * @param app, 业务名称
     * @param server, 服务名称
     * @param file
     */
    TimeLogger *logger(const string &sApp, const string &sServer,const string &sFile = "");

    /**
     * 同步写本地时间日志(远程日志一定是异步写的, 无法调整)
     * @param bSync
     */
    void sync(const string &sFile, bool bSync);

    /**
     * 远程时间日志
     * @param sFile, 文件名称, 为空表示缺省的时间日志
     * @param bEnable
     */
    void enableRemote(const string &sFile, bool bEnable);

    /**
     * 远程时间日志
     * @param sApp,应用名称
     * @param sServer,服务名称
     * @param sFile, 文件名称, 为空表示缺省的时间日志
     * @param bEnable
     */
	void enableRemoteEx(const string &sApp, const string &sServer,const string &sFile, bool bEnable);

    /**
     * 本地时间日志
     * @param sFile,文件名称, 为空表示缺省的时间日志
     * @param bEnable
     */
    void enableLocal(const string &sFile, bool bEnable);

    /**
     * 本地时间日志
     * @param sApp,应用名称
     * @param sServer,服务名称
     * @param sFile,文件名称, 为空表示缺省的时间日志
     * @param bEnable
     */
	void enableLocalEx(const string &sApp, const string &sServer,const string &sFile, bool bEnable);
	/**
	 * @brief 日志文件名是否带.log后缀
	 * @param bEnable
	 */
	void enableSufix(bool bEnable=true){_bHasSufix = bEnable;}
	/**
	 * @brief 是否允许框架在日志文件名上增加业务相关的标识
	 * @param bEnable
	 */
	void enablePrefix(bool bEnable=true){_bHasAppNamePrefix = bEnable;}
	/**
	 * @brief 日志文件名中用户自定义字符与日期字符间的连接符，默认是"_"
	 * @param str
	 */
	void setFileNameConcatStr(const string& str) {_sConcatStr = str;}

	/**
	 * @brief 框架中增加的日志内容之间的分割符，默认是"|"
	 * @param str
	 */
	void setSeparator(const string& str) {_sSepar = str;}

	/**
	 * @brief 框架中日期和时间之间是否需要加中括号[],有些统计由特殊需求；默认不加
	 * @param bEnable
	 */
	void enableSqareWrapper(bool bEnable) {_bHasSquareBracket = bEnable;}

protected:

    /**
     * 初始化时间日志
     * @param pTimeLogger
     * @param sFile
     * @param sFormat
     */
    void initTimeLogger(TimeLogger *pTimeLogger, const string &sFile, const string &sFormat);

    /**
     * 初始化时间日志
     * @param pTimeLogger
     * @param sApp
     * @param sServer
     * @param sFile
     * @param sFormat
     */

    void initTimeLogger(TimeLogger *pTimeLogger,const string &sApp, const string &sServer, const string &sFile, const string &sFormat);

protected:

    /**
     * 通信器
     */
    CommunicatorPtr         _comm;

    /**
     * 远程服务句柄
     */
    LogPrx                  _logPrx;

    /**
     * 应用
     */
    string                  _sApp;

    /**
     * 服务名称
     */
    string                  _sServer;

    /**
     * 日志路径
     */
    string                  _sLogpath;

    /**
     * 缺省按天日志
     */
    TimeLogger              *_pDefaultLogger;

    /**
     * 远程日志
     */
    map<string, TimeLogger*>    _loggers;
    /**
     * set分组信息
     */
    string                  _sSetDivision;

	/**
	 * 是否带.log后缀
	 */
	bool					_bHasSufix;
	/**
	 * 是否允许框架在日志文件名上增加业务相关的标识
	 */
	bool 					_bHasAppNamePrefix;

	/**
	 * 日志文件名中用户自定义字符与日期字符间的连接符，默认是"_"
	 */
	string 					_sConcatStr;
	/**
	 * 分隔符
	 */
	string        _sSepar;
	/**
	 * 日期部分是否加上[]
	 */
	bool 		  _bHasSquareBracket;
};

/**
 * 染色开关类，析构时关闭
 */
class TafDyeingSwitch
{
public:
    /**
     * 构造函数，默认不打开染色日志
     */
    TafDyeingSwitch()
    :bNeedDyeing(false)
    ,sDyeingKey("")
    {
    }

    /**
     * 析构函数，关闭已打开的染色日志
     */
    ~TafDyeingSwitch()
	{
		if(bNeedDyeing)
		{
			TafRollLogger::getInstance()->enableDyeing(false);

			ServantProxyThreadData* td = ServantProxyThreadData::getData();
			if (td)
			{
				td->data()->_bDyeing = false;
                td->data()->_dyeingKey = "";
			}
		}
	}

	/**
	 * 获取染色的key
	 *
	 * @author coonzhang (2011/8/19)
	 * @param key
	 * @return bool
	 */
	static bool getDyeingKey(string& key)
	{
		ServantProxyThreadData* td = ServantProxyThreadData::getData();

		if (td && td->data()->_bDyeing == true)
		{
			key = td->data()->_dyeingKey;

			return true;
		}
		return false;
	}

    /**
     * 启用染色日志
     */
    void enableDyeing(const string& dyeingKey = "")
	{
		TafRollLogger::getInstance()->enableDyeing(true, dyeingKey);

		ServantProxyThreadData* td = ServantProxyThreadData::getData();
		if (td)
		{
			td->data()->_bDyeing	= true;
            td->data()->_dyeingKey = dyeingKey;
		}

		bNeedDyeing = true;
        sDyeingKey = dyeingKey;
	}

protected:
    bool bNeedDyeing;
    string sDyeingKey;
};

#ifndef DO_NOT_DEFINE_LOG_FDLOG
/**
 * 循环日志
 */
#define LOG             (TafRollLogger::getInstance()->logger())

/**
 * @brief 按级别循环日志宏
 *
 * @param level 日志等级,TafRollLogger::INFO_LOG,TafRollLogger::DEBUG_LOG,TafRollLogger::WARN_LOG,TafRollLogger::ERROR_LOG
 * @msg 日志内容语句,包括<<重定向符连接的语句,如 "Demo begin" << " testing !" <<endl;
 *
 * @用法:
 *       标准输出流方式: cout << "I have " << vApple.size() << " apples!"<<endl;
 *       框架宏方式:     LOGMSG(TafRollLogger::INFO_LOG,"I have " << vApple.size() << " apples!"<<endl);
 */
#define LOGMSG(level,msg...) do{ if(LOG->IsNeedLog(level)) LOG->log(level)<<msg;}while(0)

/**
 * @brief 按级别循环日志
 *
 * @msg 日志内容语句,包括<<重定向符连接的语句,如 "Demo begin" << " testing !" <<endl;
 *
 * @用法:
 *       标准输出流方式: cout << "I have " << vApple.size() << " apples!"<<endl;
 *       框架宏方式:     LOGINFO("I have " << vApple.size() << " apples!"<<endl);
 */
#define LOGINFO(msg...)    LOGMSG(TafRollLogger::INFO_LOG,msg)
#define LOGDEBUG(msg...)   LOGMSG(TafRollLogger::DEBUG_LOG,msg)
#define LOGWARN(msg...)    LOGMSG(TafRollLogger::WARN_LOG,msg)
#define LOGERROR(msg...)   LOGMSG(TafRollLogger::ERROR_LOG,msg)


/**
 * 按天日志
 */
#define DLOG            (TafTimeLogger::getInstance()->logger()->any())
#define FDLOG(x)        (TafTimeLogger::getInstance()->logger(x)->any())
#define FFDLOG(x,y,z)   (TafTimeLogger::getInstance()->logger(x,y,z)->any())

/**
 * 按天日志
 * @param swith 远程日志开关
 * @sApp
 * @sServer
 * @sFile
 */
#define ENREMOTE_FDLOG(swith,sApp,sServer,sFile) (TafTimeLogger::getInstance()->enableRemoteEx(sApp,sServer,sFile,swith))
#define ENLOCAL_FDLOG(swith,sApp,sServer,sFile) (TafTimeLogger::getInstance()->enableLocalEx(sApp,sServer,sFile,swith))

#endif

}

#endif

