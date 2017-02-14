#ifndef ALARMS_H
#define ALARMS_H

#include "types.h"

/**This data type represents count values in ticks.*/
typedef int TickType;
/**This data type points to the data type TickType.*/
typedef TickType* TickRefType;
/**This data type represents a structure for storage of counter characteristics.*/
typedef struct {
	/**Maximum possible allowed count value in ticks.*/
	TickType maxallowedvalue;
	/**Number of ticks required to reach a counter-specific (significant) unit.*/
	TickType ticksperbase;
	/**Smallest allowed value for the <cycle>-parameter of SetRelAlarm/SetAbsAlarm (only for systems with extended status).*/
	TickType min<cycle>;
} AlarmBaseType;
/**This data type points to the data type AlarmBaseType.*/
typedef AlarmBaseType* AlarmBaseRefType;
/**This data type represents an alarm object.*/
typedef int AlarmType;

/**
 * @brief DeclareAlarm serves as external declaration of an alarm element.
 *
 * @param[in] AlarmIdentifier Alarm identifier (C-identifier).
 */
#define DeclareAlarm( AlarmIdentifier )													\
extern AlarmType ##AlarmIdentifier;														\
/*Maximum possible allowed value of counter ##AlarmIdentifier in ticks*/				\
extern const TickType OSMAXALLOWEDVALUE_##AlarmIdentifier;								\
/**Number of ticks required to reach a specific unit of counter ##AlarmIdentifier.*/	\
extern const TickType OSTICKSPERBASE_##AlarmIdentifier;									\
/**Minimum allowed number of ticks for a cyclic alarm of counter ##AlarmIdentifier.*/	\
extern const TickType OSMINCYCLE_##AlarmIdentifier;

/**
 * The system service GetAlarmBase reads the alarm base characteristics. The return value <Info> is a structure in which the information of data type AlarmBaseType is stored.
 *
 * @remark Allowed on task level, ISR, and in several hook routines (see Figure 12-1).

 *
 * @param[in] AlarmID Reference to alarm
 * @param[out] Info Reference to structure with constants of the alarm base.
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Alarm <AlarmID> is invalid, E_OS_ID.
 */
StatusType GetAlarmBase( AlarmType AlarmID, AlarmBaseRefType Info );

/**
 * The system service GetAlarm returns the relative value in ticksbefore the alarm AlarmID expires.
 * 
 * @remark It is up to the application to decide whether for example a CancelAlarm may still be useful.
 * @remark If AlarmID is not in use, Tick is not defined.
 * @remark Allowed on task level, ISR, and in several hook routines (see Figure 12-1).
 *
 * @param[in] AlarmID Reference to an alarm.
 * @param[out] Tick Relative value in ticks before the alarm AlarmID expires.
 *
 * @return [Standard] No error, E_OK.
 * @return [Standard] Alarm <AlarmID> is not used, E_OS_NOFUNC.
 * @return [Extended] Alarm <AlarmID> is invalid, E_OS_ID.
 */
StatusType GetAlarm( AlarmType AlarmID, TickRefType Tick);

/**
 * The system service occupies the alarm <AlarmID> element. After <increment> ticks have elapsed, the task assigned to the alarm <AlarmID> is activated or the assigned event (only forextended tasks) is set or the alarm-callback routine is called.
 *
 * @remark The behaviour of <increment> equal to 0 is up to the implementation.
 * @remark If the relative value <increment> is very small, the alarm may expire, and the task may become ready or the alarm-callback may be called before the system service returns to the user.
 * @remark If <cycle> is unequal zero, the alarm element is logged on again immediately after expiry with the relative value <cycle>.
 * @remark The alarm <AlarmID> must not already be in use.
 * @remark To change values of alarms already in use the alarm shall be cancelled first.
 * @remark If the alarm is already in use, this call will be ignored and the error E_OS_STATE is returned.
 * @remark Allowed on task level and in ISR, but not in hook routines.
 *
 * @param[in] AlarmID Reference to the alarm element.
 * @param[in] increment Relative value in ticks.
 * @param[in] cycle Cycle value in case of cyclic alarm. In case of single alarms, <cycle> shall be zero.
 *
 * @return [Standard] No error, E_OK.
 * @return [Standard] Alarm <AlarmID> is already in use, E_OS_STATE.
 * @return [Extended] Alarm <AlarmID> is invalid, E_OS_ID.
 * @return [Extended] Value of <increment> outside of the admissible limits (lower than zero or greater than maxallowedvalue), E_OS_VALUE.
 * @return [Extended] Value of <cycle> unequal to 0 and outside of the admissible counter limits (less than min<cycle> or greater than maxallowedvalue), E_OS_VALUE.
 */
StatusType SetRelAlarm( AlarmType AlarmID, TickType increment, TickType cycle );

/**
 * The system service occupies the alarm <AlarmID> element. When <start> ticks are reached, the task assigned to the alarm <AlarmID> is activated or the assigned event (only for extended tasks) is set or the alarm-callback routine is called.
 * 
 * @remark If the absolute value <start> is very close to the current counter value, the alarm may expire, and the task may become ready or the alarm-callback may be called before the system service returns to the user.
 * @remark If the absolute value <start> already was reached before the system call, the alarm shall only expire when the absolute value <start> is reached again, i.e. after the next overrun of the counter.
 * @remark If <cycle> is unequal zero, the alarm element is logged on again immediately after expiry with the relative value <cycle>.
 * @remark The alarm <AlarmID> shall not already be in use.
 * @remark To change values of alarms already in use the alarm shall be cancelled first.
 * @remark If the alarm is already in use, this call will be ignored and the error E_OS_STATE is returned.
 * @remark Allowed on task level and in ISR, but not in hook routines.
 *
 * @param[in] AlarmID Reference to the alarm element.
 * @param[in] start Absolute value in ticks.
 * @param[in] cycle Cycle value in case of cyclic alarm. In case of single alarms, cycle shall be zero.
 *
 * @return [Standard] No error, E_OK.
 * @return [Standard] Alarm <AlarmID> is already in use, E_OS_STATE.
 * @return [Extended] Alarm <AlarmID> is invalid, E_OS_ID.
 * @return [Extended] Value of <start> outside of the admissible counter limit (less than zero or greater than maxallowedvalue), E_OS_VALUE.
 * @return [Extended] Value of <cycle> unequal to 0 and outside of the admissible counter limits (less than mincycle or greater than maxallowedvalue), E_OS_VALUE.
 */
StatusType SetAbsAlarm( AlarmType AlarmID, TickType start, TickType cycle );

/**
 * The system service cancels the alarm <AlarmID>.
 * 
 * @remark Allowed on task level and in ISR, but not in hook routines.

 * 
 * @param[in] AlarmID Reference to an alarm.
 *
 * @return [Standard] No error, E_OK.
 * @return [Standard] Alarm <AlarmID> not in use, E_OS_NOFUNC.
 * @return [Extended] Alarm <AlarmID> is invalid, E_OS_ID.
 */
StatusType CancelAlarm( AlarmType AlarmID );

//There always exists at least one counter which is a time counter (system counter).*/
extern AlarmType AlarmSystemCounter;
//The constants of this counter are additionally accessible via the following constants:
/*Maximum possible allowed value for the System Counter in ticks*/
extern const TickType OSMAXALLOWEDVALUE;
/**Number of ticks required to reach a specific unit for the System Counter.*/
extern const TickType OSTICKSPERBASE;
/**Minimum allowed number of ticks for the System Counter.*/
extern const TickType OSMINCYCLE;
/**Duration of a tick of the System Counter in nanoseconds.*/
extern const TickType OSTICKDURATION;

/**
 * Defines an Alarm callback function.
 *
 * @param AlarmCallBackName The alarm call backname will be Func + whatever you typed.
 *
 * @todo Add return statments
 */
#define ALARMCALLBACK( AlarmCallBackName ) StatusType Func##AlarmCallBackName(void)

#endif//ALARMS_H