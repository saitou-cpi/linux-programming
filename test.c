########################################################
# ID:               519-AWS-112 (MOCK)
# Name:             519-AWS-112_StopAuroraMock.py
# Summary:          MOCK: return 200 without calling AWS
# Arguments:        AUR_NAME
# Return Value:     200(success), 500(fail)
########################################################
import os
from CommonLayer import GetLogger, StartScript, EndScript

logger = GetLogger(__name__)
script_name = "519-AWS-112_StopAuroraMock"

def lambda_handler(event, context):
    StartScript(logger, script_name)

    aur_name = (event or {}).get("AUR_NAME")
    if not aur_name:
        logger.error("'AUR_NAME' key missing in event payload.",
                     extra={"message_id":"519-AWS-112-02"})
        logger.error("Lambda function execution failed.",
                     extra={"message_id":"519-AWS-112-03"})
        return {"statusCode": 500}

    logger.info(f"[MOCK] Would call stop_db_cluster for '{aur_name}'.",
                extra={"message_id":"519-AWS-112-01"})

    EndScript(logger, script_name)
    return {"statusCode": 200}
