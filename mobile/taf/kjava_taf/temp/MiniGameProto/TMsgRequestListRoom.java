// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 1.5.1 by WSRD Tencent.
// Generated from `/usr/local/resin_system.mqq.com/webapps/communication/taf/upload/MiniGameProto_new.jce'
// **********************************************************************

package MiniGameProto;

public final class TMsgRequestListRoom extends com.qq.taf.jce.JceStruct
{
    public String className()
    {
        return "MiniGameProto.TMsgRequestListRoom";
    }

    public short nGameID = (short)0;

    public short nZoneID = (short)0;

    public short nPage = (short)0;

    public short nRoomNumPerPage = (short)0;

    public short getNGameID()
    {
        return nGameID;
    }

    public void  setNGameID(short nGameID)
    {
        this.nGameID = nGameID;
    }

    public short getNZoneID()
    {
        return nZoneID;
    }

    public void  setNZoneID(short nZoneID)
    {
        this.nZoneID = nZoneID;
    }

    public short getNPage()
    {
        return nPage;
    }

    public void  setNPage(short nPage)
    {
        this.nPage = nPage;
    }

    public short getNRoomNumPerPage()
    {
        return nRoomNumPerPage;
    }

    public void  setNRoomNumPerPage(short nRoomNumPerPage)
    {
        this.nRoomNumPerPage = nRoomNumPerPage;
    }

    public TMsgRequestListRoom()
    {
    }

    public TMsgRequestListRoom(short nGameID, short nZoneID, short nPage, short nRoomNumPerPage)
    {
        this.nGameID = nGameID;
        this.nZoneID = nZoneID;
        this.nPage = nPage;
        this.nRoomNumPerPage = nRoomNumPerPage;
    }

    public boolean equals(Object o)
    {
        TMsgRequestListRoom t = (TMsgRequestListRoom) o;
        return (
            com.qq.taf.jce.JceUtil.equals(nGameID, t.nGameID) && 
            com.qq.taf.jce.JceUtil.equals(nZoneID, t.nZoneID) && 
            com.qq.taf.jce.JceUtil.equals(nPage, t.nPage) && 
            com.qq.taf.jce.JceUtil.equals(nRoomNumPerPage, t.nRoomNumPerPage) );
    }

    public void writeTo(com.qq.taf.jce.JceOutputStream _os)
    {
        try
        {
            _os.write(nGameID, 0);
            _os.write(nZoneID, 1);
            _os.write(nPage, 2);
            _os.write(nRoomNumPerPage, 3);
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
            nGameID = 0;
            nGameID = (short) _is.read(nGameID, 0, true);

            nZoneID = 0;
            nZoneID = (short) _is.read(nZoneID, 1, true);

            nPage = 0;
            nPage = (short) _is.read(nPage, 2, true);

            nRoomNumPerPage = 0;
            nRoomNumPerPage = (short) _is.read(nRoomNumPerPage, 3, true);

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
