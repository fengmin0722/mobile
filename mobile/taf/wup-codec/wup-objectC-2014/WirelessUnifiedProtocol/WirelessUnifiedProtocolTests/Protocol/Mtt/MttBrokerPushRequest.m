// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 2.1.4.2 by WSRD Tencent.
// Generated from `/usr/local/resin_system.mqq.com/webapps/communication/taf/upload/renjunyi/MTT.jce'
// **********************************************************************

#import "MttBrokerPushRequest.h"

@implementation MttBrokerPushRequest

@synthesize JV2_PROP_NM(o,0,stUserInfo);
@synthesize JV2_PROP_NM(o,1,strCookie);
@synthesize JV2_PROP_NM(r,2,iPushTime);
@synthesize JV2_PROP_EX(r,3,vPushAppReqData,VOMTTPushAppReqList);

+ (void)initialize
{
    if (self == [MttBrokerPushRequest class]) {
        [MttBrokerUserInfo initialize];
        [MttPushAppReqList initialize];
        [super initialize];
    }
}

- (id)init
{
    if (self = [super init]) {
        JV2_PROP(strCookie) = DefaultJceString;
        JV2_PROP(vPushAppReqData) = DefaultJceArray;
    }
    return self;
}

- (void)dealloc
{
    JV2_PROP(stUserInfo) = nil;
    JV2_PROP(strCookie) = nil;
    JV2_PROP(vPushAppReqData) = nil;
    [super dealloc];
}

+ (NSString*)jceType
{
    return @"MTT.BrokerPushRequest";
}

@end