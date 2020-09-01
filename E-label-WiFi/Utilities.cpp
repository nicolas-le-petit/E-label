// /* 
// Date  : 04/08/2020
// Author: DungTT
// Provide Utilities functions for program.
// Including: 
// Check timeout (miliseconds)
//  */

// #include "Utilities.h"

// /*
// @date : 04/08/2020
// @brief: check time out
// @para : pointer of timer var
//         interval
//  */

// bool check_timeout(unsigned long *from, unsigned long interval)
// {
// 	if (millis() - (*from) >= interval){
// 		*from = millis();
// 		return true;
// 	}
// 	return false;
// }

// // void Task_Error_Handler(const char *file, unsigned long line)
// // {
// // 	/* debug("Task Error:\nFile: %s\nLine: %d\n", file, line); */
// //     Serial.println();
// // 	while(1);
// // }