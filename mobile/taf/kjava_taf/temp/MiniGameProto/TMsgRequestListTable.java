// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 1.5.1 by WSRD Tencent.
// Generated from `/usr/local/resin_system.mqq.com/webapps/communication/taf/upload/MiniGameProto_new.jce'
// **********************************************************************

package MiniGameProto;

public final class TMsgRequestListTable extends com.qq.taf.jce.JceStruct
{
    public String className()
    {
        return "MiniGameProto.TMsgRequestListTable";
    }

    public short nZoneID = (short)0;

    public short nRoomID = (short)0;

    public short nPage = (short)0;

    public short nTableNumPerPage = (short)0;

    public short getNZoneID()
    {
        return nZoneID;
    }

    public void  setNZoneID(short nZoneID)
    {
        this.nZoneID = nZoneID;
    }

    public short getNRoomID()
    {
        return nRoomID;
    }

    public void  setNRoomID(short nRoomID)
    {
        this.nRoomID = nRoomID;
    }

    public short getNPage()
    {
        return nPage;
    }

    public void  setNPage(short nPage)
    {
        this.nPage = nPage;
    }

    public short getNTableNumPerPage()
    {
        return nTableNumPerPage;
    }

    public void  setNTableNumPerPage(short nTableNumPerPage)
    {
        this.nTableNumPerPage = nTableNumPerPage;
    }

    public TMsgRequestListTable()
    {
    }

    public TMsgRequestListTable(short nZoneID, short nRoomID, short nPage, short nTableNumPerPage)
    {
        this.nZoneID = nZoneID;
        this.nRoomID = nRoomID;
        this.nPage = nPage;
        this.nTableNumPerPage = nTableNumPerPage;
    }

    public boolean equals(Object o)
    {
        TMsgRequestListTable t = (TMsgRequestListTable) o;
        return (
            com.qq.taf.jce.JceUtil.equals(nZoneID, t.nZoneID) && 
            com.qq.taf.jce.JceUtil.equals(nRoomID, t.nRoomID) && 
            com.qq.taf.jce.JceUtil.equals(nPage, t.nPage) && 
            com.qq.taf.jce.JceUtil.equals(nTableNumPerPage, t.nTableNumPerPage) );
    }

    public void writeTo(com.qq.taf.jce.JceOutputStream _os)
    {
        try
        {
            _os.write(nZoneID, 0);
            _os.write(nRoomID, 1);
            _os.write(nPage, 2);
            _os.write(nTableNumPerPage, 3);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public void readFrom(com.qq.taf.jce.JceInputStream _is)
    {
        try
        {
            nZoneID = 0;
            nZoneID = (short) _is.read(nZoneID, 0, true);

            nRoomID = 0;
            nRoomID = (short) _is.read(nRoomID, 1, true);

            nPage = 0;
            nPage = (short) _is.read(nPage, 2, true);

            nTableNumPerPage = 0;
            nTableNumPerPage = (short) _is.read(nTableNumPerPage, 3, true);

        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    public void display(java.lang.StringBuffer _os, int _level)
    {
    }

}
