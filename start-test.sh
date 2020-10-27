#!/bin/bash

# parse parameters, https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash
POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    --output-dir)
    TARGET_DIR="$2"
    shift # past argument
    shift # past value
    ;;
    --dl-earfcn)
    export DL_EARFCN="$2"
    shift # past argument
    shift # past value
    ;;
    --apn)
    export APN="$2"
    shift # past argument
    shift # past value
    ;;
    --imei)
    export IMEI="$2"
    shift # past argument
    shift # past value
    ;;
    --default)
    DEFAULT=YES
    shift # past argument
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

if [[ -z "$DL_EARFCN" || -z "$APN" || -z "$IMEI" ]]; then
    echo "usage: start-test.sh --dl-earfcn earfcn --apn apn --imei imei"
    echo "optional: --output-dir"
    exit 1
fi
if [[ -z "$TARGET_DIR" ]]; then
    TARGET_DIR=$(mktemp -d)
fi

START_DATE=$(date +%Y-%m-%d_%H:%M)

echo "Writing to ${TARGET_DIR} on host."
for DIR in config pcap log; do
    mkdir ${TARGET_DIR}/${DIR}
    if [[ $? -ne 0 ]]; then
        echo "Error creating directory '${TARGET_DIR}/${DIR}', does the target exist and is writable?"
        exit 1
    fi
done

# fill in template config from parameters
envsubst < ./srsue/ciphercheck.conf.example > ${TARGET_DIR}/config/ciphercheck.conf

# we need access to USB; run privileged
sudo docker run \
    --privileged \
    -v ${TARGET_DIR}/config/ciphercheck.conf:/etc/srslte/ciphercheck.conf \
    -v $(realpath ${TARGET_DIR}):/tmp/results \
    lte-ciphercheck

END_DATE=$(date +%Y-%m-%d_%H:%M)

echo "Started ${START_DATE}, finished ${END_DATE}"
echo "Results written to ${TARGET_DIR} on host."
