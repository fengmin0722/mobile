// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 2.1.4.2 by WSRD Tencent.
// Generated from `/usr/local/resin_system.mqq.com/webapps/communication/taf/upload/renjunyi/MTT.jce'
// **********************************************************************

#import "MttWeatherInfo4Mini.h"

@implementation MttWeatherInfo4Mini

@synthesize JV2_PROP_NM(o,0,sDate);
@synthesize JV2_PROP_NM(o,1,sDweather);
@synthesize JV2_PROP_NM(o,2,iMaxT);
@synthesize JV2_PROP_NM(o,3,iMinT);
@synthesize JV2_PROP_NM(o,4,sMoreUrl);

+ (void)initialize
{
    if (self == [MttWeatherInfo4Mini class]) {
        [super initialize];
    }
}

- (id)init
{
    if (self = [super init]) {
        JV2_PROP(sDate) = DefaultJceString;
        JV2_PROP(sDweather) = DefaultJceString;
        JV2_PROP(sMoreUrl) = DefaultJceString;
    }
    return self;
}

- (void)dealloc
{
    JV2_PROP(sDate) = nil;
    JV2_PROP(sDweather) = nil;
    JV2_PROP(sMoreUrl) = nil;
    [super dealloc];
}

+ (NSString*)jceType
{
    return @"MTT.WeatherInfo4Mini";
}

@end