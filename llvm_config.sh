#!/usr/bin/env bash

if [ hash `llvm-config 2>/dev/null` ] && [ ! -f /etc/ld.so.conf.d/llvm.conf ];
then
	echo `llvm-config --libdir` >> /etc/ld.so.conf.d/llvm.conf
	ldconfig
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:`llvm-config --libdir`
	echo "Added llvm lib dir to ldconfig"
fi