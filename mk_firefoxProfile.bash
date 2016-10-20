#!/bin/bash

# Makes an empty firefox profile so we may use it to launch an independent
# firefox process.  This script works for firefox version (firefox
# --version): "Mozilla Firefox 49.0" on Xubuntu 16.04.  We expect this
# script will break as firefox changes.

# exit on error
set -e
ini=${HOME}/.mozilla/firefox/profiles.ini

scriptdir="$(dirname $0)"
cd $scriptdir



function usage()
{
    cat << EOF

  Usage: $0 PROFILE_NAME DIR

    Create a firefox profile in the directory DIR and add additions to
  the file $ini to make this profile usable.  DIR must be full path.

EOF

    exit 1
}

[ -n "$2" ] || usage




profile=$1
dir=$2


if [ -e $dir ] ; then
    echo "$dir exists already"
    exit 1
fi


if grep -q -e "^Name=$profile\$" $ini  ; then
    echo "Looks like the profile $profile exists in $ini already"
    echo "That may be okay ..."
else
    count=1
    # [Profile1] or [Profile2] or ...
    Profile=Profile$count
    while grep -q "\[${Profile}\]" $ini ; do
        let count=$count+1
        Profile=Profile$count
    done

    echo "Adding [$Profile] Name=$profile to $ini"

    set -x
    cat << EOF >> $ini
[$Profile]
Name=$profile
IsRelative=0
Path=${dir}

EOF

fi

set +x
echo "making firefox profile files at $dir/"
set -x


time="$(date +%s)999"


mkdir $dir

cat << EOF > $dir/times.json
{
"created": $time
}
EOF

chmod 700 $dir/times.json
mkdir $dir/extensions
chmod 700 $dir/extensions

set -x

cat << EOF

Try is out with command:

  firefox -P $profile ./045_xx_intervalAnimate/run.html

EOF

