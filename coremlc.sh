if [ -z $1 ] || [ -z $2 ] ; then
    echo "usage $0 <input .mlmodel file> <output dir for .mlmodelc>"
    exit -1
fi
#/Applications/Xcode.app/Contents/Developer/usr/bin/coremlc compile $1 $2 --deployment-target 13.0 --platform ios
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/coremlcompiler compile $1 $2 --deployment-target 13.0 --platform ios
