/******* Clinic Management Header File  *****/
/******* Author : Mahmoud Rajab Mohamed *****/

#ifndef CLINIC_MANAGEMENT_H
#define CLINIC_MANAGEMENT_H




typedef struct Patient
{
	u8 Name[20];
	u32 Age;
	u8 Gender[6];
	u32 ID;			// Unique 
	u32 SlotNum;		// Unique
	
}Patient;

//----------------------------< Admin Functions >------------------------------------

u8 Add_Patient(void);

void Edit_Patient(void);

void Reserve_Slot(void);

void Cancel_Reservation(void);

//---------------------------< User Function >---------------------------------------

u8 View_Patient(void);
void View_TodayReservation(void);


#endif 