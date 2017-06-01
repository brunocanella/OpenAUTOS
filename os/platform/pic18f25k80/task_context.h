#ifndef PIC18F25K80_TASK_CONTEXT_H
#define PIC18F25K80_TASK_CONTEXT_H

#include <stdint.h>
#include <xc.h>

#include "../../types.h"
#include "../../constants.h"

#define PLATFORM_CONTEXT_STACK_SIZE 31

/**Retrives the value part of the uController Stack */
#define uControllerStackValue() ( STKPTRbits.STKPTR )

typedef uint32_t PlatformTaskContextStackType;
typedef PlatformTaskContextStackType* PlatformTaskContextStackRefType;

typedef struct {
    uint8_t work;
    uint8_t bsr;
    uint8_t status;
    PlatformTaskContextStackType stack[PLATFORM_CONTEXT_STACK_SIZE];
    uint8_t stack_top;
} PlatformTaskContextType;

typedef PlatformTaskContextType* PlatformTaskContextRefType;

/**
 * @brief (Re)Initializes the context of a task
 *
 * @param[in] Context A pointer to the task's context to be reset.
 *
 * @return No error, E_OS_OK.
 */
StatusType ResetTaskContext( PlatformTaskContextRefType Context, CallbackType Callback );

#ifndef PUSH
#define PUSH() asm(" PUSH")
#endif

#ifndef POP
#define POP() asm(" POP")
#endif

/**
 * @brief Clears the uController's stack and saves it in the current task stack.
 *
 * @param[in] TaskContextRef Context The context of the current active task
 */
#define PlatformSaveTaskContext( TaskContextRef )                               \
do {                                                                            \
    TaskContextRef->work = WREG;                                                \// Saving Work Register
    TaskContextRef->bsr = BSR;                                                  \// Saving Bank Select Register
    TaskContextRef->status = STATUS;                                            \// Saving Status Register
    PlatformTaskContextStackRefType stack = (TaskContextRef->stack);            \// Shortcut to the stack
    while( uControllerStackValue() > 0 ) {                                      \// Loops Through the values on the Stack
        uint8_t i = TaskContextRef->stack_top++;                                \//     Gets the position for the local stack and then increases the top of the local stack
        stack[i] = TOS;                                                         \//     Saves the uController's value that on the top of the stack
        POP();                                                                  \//     Removes the top most value from the uController's stack
    }                                                                           \
} while(0)

/**
 * @brief Loads the uController's stack and clears the current task stack.
 *
 * @param[in] TaskContextRef Context The context of the current active task
 */
#define PlatformLoadTaskContext( TaskContextRef, FuncNameStr )                  \
do {                                                                            \
    PlatformTaskContextStackRefType stack = (TaskContextRef->stack);            \// Shortcut to the stack
    while( TaskContextRef->stack_top > 0 ) {                                    \// Loops while there are values to push to the Stack
        uint8_t i = --TaskContextRef->stack_top;                                \//     Reduces the size of the stack and then gets the index position
        PUSH();                                                                 \//     Moves the uC stack position to the next available
        uint32_t callback = stack[i];                                           \
        uint8_t tosu = (uint8_t)(callback >> 16);                               \
        uint8_t tosh = (uint8_t)(callback >>  8);                               \
        uint8_t tosl = (uint8_t)(callback >>  0);                               \
        asm("BANKSEL("FuncNameStr"@tosu)");                                     \
        asm("MOVF (("FuncNameStr"@tosu) and 0FFh),w");                          \
        asm("MOVWF TOSU");                                                      \
        asm("BANKSEL("FuncNameStr"@tosh)");                                     \
        asm("MOVF (("FuncNameStr"@tosh) and 0FFh),w");                          \
        asm("MOVWF TOSH");                                                      \
        asm("BANKSEL("FuncNameStr"@tosl)");                                     \
        asm("MOVF (("FuncNameStr"@tosl) and 0FFh),w");                          \
        asm("MOVWF TOSL");                                                      \
    }                                                                           \
    WREG = TaskContextRef->work;                                                \// Loading the Work Register
    BSR = TaskContextRef->bsr;                                                  \// Loading Bank Select Register
    STATUS = TaskContextRef->status;                                            \// Loading Status Register
} while(0)

#endif//PIC18F25K80_TASK_CONTEXT_H