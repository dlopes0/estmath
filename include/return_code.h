#pragma once

#ifndef RETURN_CODE_H
#define RETURN_CODE_H

// Default Return Codes
#define RETURN_CODE_NULL               0x00  // RETURN CODE: Idle, Initial state
#define RETURN_CODE_EVAL_OK            0x01  // RETURN CODE: Evaluation OK
#define RETURN_CODE_SYNTAX_ERROR       0x02  // RETURN CODE: Syntax Error
#define RETURN_CODE_DIV_ZERO_ERROR     0x03  // RETURN CODE: Division by Zero Error
#define RETURN_CODE_MISSING_ARGS_ERROR 0x04  // RETURN CODE: Missing Arguments Error
#define RETURN_CODE_UNKNOWN_FUNC_ERROR 0x05  // RETURN CODE: Unknown Function Error
#define RETURN_CODE_SCI_NOTATION_ERROR 0x06  // RETURN CODE: Scientific Notation Error
#define RETURN_CODE_UNKNOWN_VARS_ERROR 0x07  // RETURN CODE: Unknown Variable Error

extern char RETURN_CODE;

void return_code_set(char code);

#endif