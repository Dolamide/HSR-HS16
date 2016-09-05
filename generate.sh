#!/usr/bin/env bash
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

rm -Rf $DIR/_build/*
mkdir -p $DIR/_build/pdf/
mkdir -p $DIR/_build/html/

for dir in $DIR/*
do
    module=${dir##*/}
    if [ -d $module ] && [ $module != '_build' ]; then
        cd "$module" || exit
        echo "Generating PDF and HTML for $module"
        make clean html pdf
        cp -R _build/html ../_build/html/$module/
        cp _build/pdf/* ../_build/pdf/
        cd ../
    fi
done
cp .shared/.htaccess _build/.htaccess
