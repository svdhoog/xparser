#!/bin/bash

# Path to xparser
export FLAME_XPARSER_DIR="$PWD/../.."

cd $FLAME_XPARSER_DIR

echo "Now here: $PWD"

export TESTS="basic_agent_order message_reading"

for i in $TESTS; do

	# Parse model 
	export MODEL_DIR="$FLAME_XPARSER_DIR/tests/test_agent_order/models/$i"

	cd $FLAME_XPARSER_DIR

	./xparser $MODEL_DIR/model.xml

	cd $MODEL_DIR

	# Build model
	make clean all

done

echo 'Script done.'
