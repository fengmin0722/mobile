cd src
jcefiles=`ls *.jce`
/usr/local/taf/bin/jce2java --with-servant --base-package=com.qq.java.test. $jcefiles 



