<?php
	require_once('../tools/nel_message.php');

	class CSendService extends CCallbackClient
	{
		// wait service handler
		function WaitCallback()
		{
			$message = parent::waitMessage();

			if ($message == false)
				return false;

			switch($message->MsgName)
			{
			case "Succeed":
				break;
			default:
				return false;
			}
			return true;
		}
	}
?>
