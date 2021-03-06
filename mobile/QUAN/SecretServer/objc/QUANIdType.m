// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 2.1.4.3 by WSRD Tencent.
// Generated from `SecretBase.jce'
// **********************************************************************

#import "JceObjectV2.h"
#import "QUANIdType.h"

#if JCEV2_ENUM_ETOS_AND_STOE_SUPPORTED

@implementation QUANIdTypeHelper

+ (NSString *)etos:(QUANIdType)e
{
    switch(e){
        case QUANIdType_SECRET: return @"QUANIdType_SECRET";
        case QUANIdType_CONTENT: return @"QUANIdType_CONTENT";
        default: return @"";
    }
}

+ (QUANIdType)stoe:(NSString *)s
{
    if(isJceEnumStringEqual(s, @"QUANIdType_SECRET")) return QUANIdType_SECRET;
    if(isJceEnumStringEqual(s, @"QUANIdType_CONTENT")) return QUANIdType_CONTENT;
    return NSIntegerMin;
}

@end

#endif
