java -Dconfig=/usr/local/app//taf/tafnode/data/Java.Test/conf/TestClient.conf -Xss1m -XX:ErrorFile=/usr/local/app/taf/app_log///Java/Test/tired_jvm_error.log  -Xloggc:/usr/local/app/taf/app_log///Java/Test/tired_jvm.log  -Xmx200m -Xms200m -XX:NewSize=50m -XX:MaxNewSize=50m -XX:+UseConcMarkSweepGC -XX:CMSInitiatingOccupancyFraction=65 -verbose:gc -XX:+PrintGCDetails -XX:+PrintGCDateStamps -XX:+PrintGCTimeStamps -XX:+PrintGCApplicationStoppedTime -cp /usr/local/app/taf/tafnode/data/Java.Test/conf:/usr/local/app/taf/tafnode/data/Java.Test/bin//classes:/usr/local/app/taf/tafnode/data/Java.Test/bin/lib/* com.qq.java.test.TiredTest>>/usr/local/app/taf/app_log///Java/Test/TiredLog 2>>/usr/local/app/taf/app_log///Java/Test/TiredErrorLog &
   