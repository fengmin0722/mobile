// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 2.0.1 by WSRD Tencent.
// Generated from `StatF.jce'
// **********************************************************************

package com.qq.taf;

public final class StatMicMsgBody extends com.qq.taf.jce.JceStruct
{
    public String className()
    {
        return "com.qq.taf.StatMicMsgBody";
    }

    public int count = 0;

    public int timeoutCount = 0;

    public int execCount = 0;

    public java.util.Map<Integer, Integer> intervalCount = null;

    public long totalRspTime = 0;

    public int maxRspTime = 0;

    public int minRspTime = 0;

    public int getCount()
    {
        return count;
    }

    public void  setCount(int count)
    {
        this.count = count;
    }

    public int getTimeoutCount()
    {
        return timeoutCount;
    }

    public void  setTimeoutCount(int timeoutCount)
    {
        this.timeoutCount = timeoutCount;
    }

    public int getExecCount()
    {
        return execCount;
    }

    public void  setExecCount(int execCount)
    {
        this.execCount = execCount;
    }

    public java.util.Map<Integer, Integer> getIntervalCount()
    {
        return intervalCount;
    }

    public void  setIntervalCount(java.util.Map<Integer, Integer> intervalCount)
    {
        this.intervalCount = intervalCount;
    }

    public long getTotalRspTime()
    {
        return totalRspTime;
    }

    public void  setTotalRspTime(long totalRspTime)
    {
        this.totalRspTime = totalRspTime;
    }

    public int getMaxRspTime()
    {
        return maxRspTime;
    }

    public void  setMaxRspTime(int maxRspTime)
    {
        this.maxRspTime = maxRspTime;
    }

    public int getMinRspTime()
    {
        return minRspTime;
    }

    public void  setMinRspTime(int minRspTime)
    {
        this.minRspTime = minRspTime;
    }

    public StatMicMsgBody()
    {
        setCount(count);
        setTimeoutCount(timeoutCount);
        setExecCount(execCount);
        setIntervalCount(intervalCount);
        setTotalRspTime(totalRspTime);
        setMaxRspTime(maxRspTime);
        setMinRspTime(minRspTime);
    }

    public StatMicMsgBody(int count, int timeoutCount, int execCount, java.util.Map<Integer, Integer> intervalCount, long totalRspTime, int maxRspTime, int minRspTime)
    {
        setCount(count);
        setTimeoutCount(timeoutCount);
        setExecCount(execCount);
        setIntervalCount(intervalCount);
        setTotalRspTime(totalRspTime);
        setMaxRspTime(maxRspTime);
        setMinRspTime(minRspTime);
    }

    public boolean equals(Object o)
    {
        StatMicMsgBody t = (StatMicMsgBody) o;
        return (
            com.qq.taf.jce.JceUtil.equals(count, t.count) && 
            com.qq.taf.jce.JceUtil.equals(timeoutCount, t.timeoutCount) && 
            com.qq.taf.jce.JceUtil.equals(execCount, t.execCount) && 
            com.qq.taf.jce.JceUtil.equals(intervalCount, t.intervalCount) && 
            com.qq.taf.jce.JceUtil.equals(totalRspTime, t.totalRspTime) && 
            com.qq.taf.jce.JceUtil.equals(maxRspTime, t.maxRspTime) && 
            com.qq.taf.jce.JceUtil.equals(minRspTime, t.minRspTime) );
    }

    public java.lang.Object clone()
    {
        java.lang.Object o = null;
        try
        {
            o = super.clone();
        }
        catch(CloneNotSupportedException ex)
        {
            assert false; // impossible
        }
        return o;
    }

    public void writeTo(com.qq.taf.jce.JceOutputStream _os)
    {
        _os.write(count, 0);
        _os.write(timeoutCount, 1);
        _os.write(execCount, 2);
        _os.write(intervalCount, 3);
        _os.write(totalRspTime, 4);
        _os.write(maxRspTime, 5);
        _os.write(minRspTime, 6);
    }

    static java.util.Map<Integer, Integer> cache_intervalCount;

    public void readFrom(com.qq.taf.jce.JceInputStream _is)
    {
        setCount((int) _is.read(count, 0, true));

        setTimeoutCount((int) _is.read(timeoutCount, 1, true));

        setExecCount((int) _is.read(execCount, 2, true));

        if(null == cache_intervalCount)
        {
            cache_intervalCount = new java.util.HashMap<Integer, Integer>();
            Integer __var_1 = 0;
            Integer __var_2 = 0;
            cache_intervalCount.put(__var_1, __var_2);
        }
        setIntervalCount((java.util.Map<Integer, Integer>) _is.read(cache_intervalCount, 3, true));

        setTotalRspTime((long) _is.read(totalRspTime, 4, true));

        setMaxRspTime((int) _is.read(maxRspTime, 5, true));

        setMinRspTime((int) _is.read(minRspTime, 6, true));

    }

    public void display(java.lang.StringBuilder _os, int _level)
    {
        com.qq.taf.jce.JceDisplayer _ds = new com.qq.taf.jce.JceDisplayer(_os, _level);
        _ds.display(count, "count");
        _ds.display(timeoutCount, "timeoutCount");
        _ds.display(execCount, "execCount");
        _ds.display(intervalCount, "intervalCount");
        _ds.display(totalRspTime, "totalRspTime");
        _ds.display(maxRspTime, "maxRspTime");
        _ds.display(minRspTime, "minRspTime");
    }

}

