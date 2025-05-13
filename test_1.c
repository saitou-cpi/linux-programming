#!/bin/bash
###########################################################
# ID :             519-OPS-001
# Name :           519-OPS-001_TrellixConfig.conf
# Summary :        McAfee Script Common Setting ( for Linux)
# Arguments :      None
# Return Value :   None
#
# All Rights Reserved, Copyright(C) SCSK LIMITED 2021
###########################################################

###########################################################
# Define McAfee Common valiable
###########################################################

#----------------------------------------------------------
# McAfee Command related
#----------------------------------------------------------
# ENS Command Directory
export ENS_SCRIPT_DIR="/opt/McAfee/ens/tp/bin"

# ENS Fullscan Task Name
export ENS_FULLSCAN_TASK_NAME="Full Scan"

# ENS Update Task Name
export ENS_UPDATE_TASK_NAME="Default Client Update task"

# ENS Fullscan Index No. Get Command
export ENS_FULLSCAN_INDEX_NO_CMD="${ENS_SCRIPT_DIR}/mfetpcli --listtasks | grep \"${ENS_FULLSCAN_TASK_NAME}\" | awk '{print \$1}' | cut -c 2-"

# ENS Update Index No. Get Command
export ENS_UPDATE_INDEX_NO_CMD="${ENS_SCRIPT_DIR}/mfetpcli --listtasks | grep \"${ENS_UPDATE_TASK_NAME}\" | awk '{print \$1}' | cut -c 2-"

# # ENS Fullscan Index No.
export ENS_FULLSCAN_INDEX_NO=$(eval ${ENS_FULLSCAN_INDEX_NO_CMD})

# # ENS Update Index No.
export ENS_UPDATE_INDEX_NO=$(eval ${ENS_UPDATE_INDEX_NO_CMD})

# ENS Fullscan Command
export ENS_FULLSCAN_CMD="${ENS_SCRIPT_DIR}/mfetpcli --runtask --index ${ENS_FULLSCAN_INDEX_NO}"

# ENS Fullscan Cancel Command
export ENS_FULLSCAN_CANCEL_CMD="${ENS_SCRIPT_DIR}/mfetpcli --stoptask --index ${ENS_FULLSCAN_INDEX_NO}"

# ENS Update Command
export ENS_UPDATE_CMD="${ENS_SCRIPT_DIR}/mfetpcli --runtask --index ${ENS_UPDATE_INDEX_NO}"

# ENS Fullscan Status Command
export ENS_FULLSCAN_STATUS_CMD="${ENS_SCRIPT_DIR}/mfetpcli --listtasks | grep \"${ENS_FULLSCAN_TASK_NAME}\" | grep -Eo 'Not Started|Initiated|Completed|Aborted|Running|Stopping|Stopped'"

# ENS Update Status Command
export ENS_UPDATE_STATUS_CMD="${ENS_SCRIPT_DIR}/mfetpcli --listtasks | grep \"${ENS_UPDATE_TASK_NAME}\" | grep -Eo 'Not Started|Initiated|Completed|Aborted|Running'"

#----------------------------------------------------------
# Script Processing related
#----------------------------------------------------------
# Script Execution user
export TRELLIX_SCRIPT_EXEC_USER="root"

# Fullscan Timeout Seconds
export FULLSCAN_TIMEOUT=7200

# Update Timeout Seconds
export UPDATE_TIMEOUT=600

# Cancel Timeout Seconds
export CANCEL_TIMEOUT=300

# Loop Wait Time Seconds
export LOOP_WAIT_TIME=10

#----------------------------------------------------------
# Script Status related
#----------------------------------------------------------
# Fullscan
export MSG_FULLSCAN_START="Initiated"
export MSG_FULLSCAN_RUNNING="Running"
export MSG_FULLSCAN_STOPPING="Stopping"
export MSG_FULLSCAN_COMPLETE="Completed"
export MSG_FULLSCAN_CANCEL="Stopped"
export MSG_FULLSCAN_ABORT="Aborted"
export MSG_FULLSCAN_NOTSTART="Not Started"

# Update
export MSG_UPDATE_START="Initiated"
export MSG_UPDATE_RUNNING="Running"
export MSG_UPDATE_COMPLETE="Completed"
export MSG_UPDATE_ABORT="Aborted"
export MSG_UPDATE_NOTSTART="Not Started"
