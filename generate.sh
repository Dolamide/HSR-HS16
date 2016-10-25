#!/usr/bin/env bash
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

rm -Rf $DIR/output/*
mkdir -p $DIR/output/pdf/
mkdir -p $DIR/output/html/

for dir in $DIR/*
do
    module=${dir##*/}
    if [ -d $module ] && [ $module != 'output' ] && [ $module != 'BuPl' ]; then
        set -e
        echo "Generating HTML for $module"
        raphidoc -d $module html
        echo "Generating PDF for $module"
        raphidoc -d $module pdf
        cp -R $module/output/html/ output/html/$module/
        cp $module/output/pdf/index.pdf output/pdf/$module.pdf
    fi
done
cp .htaccess output/.htaccess
