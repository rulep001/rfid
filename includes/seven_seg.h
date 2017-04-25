
// Permission to copy is granted provided that this header remains intact.
// This software is provided with no warranties.

////////////////////////////////////////////////////////////////////////////////

#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

// Seven Seg Enumeration of characters
enum sevenSeg {
//	_           _     _           _     _     _     _     _     _           _           _     _
// | |     |    _|    _|   |_|   |_    |_      |   |_|   |_|   |_|   |_    |      _|   |_    |_
// |_|     |   |_     _|     |    _|   |_|     |   |_|    _|   | |   |_|   |_    |_|   |_    |        .
   SS_0, SS_1, SS_2, SS_3, SS_4, SS_5, SS_6, SS_7, SS_8, SS_9, SS_A, SS_B, SS_C, SS_D, SS_E, SS_F, SS_DP,
//  _                                   _     _           _     _                                         _                 _
// |     |_|   |_    |       |   |      _    | |    _    |_|   |      _    |_    | |         | |   |_|    _    |_|    _|    _|
// |_|   | |   |_|   |     |_|   |_    | |   | |   | |   |     |     |     |_    |_|   |_|    _           _     _|   |     | |
   SS_G, SS_H, SS_h, SS_I, SS_J, SS_L, SS_m, SS_N, SS_n, SS_P, SS_R, SS_r, SS_t, SS_U, SS_u, SS_V, SS_v, SS_X, SS_Y, SS_Z, SS_lambda,
//                                                    _
// |_  	      _|       | |       | |                           |_        |           |
// |           |       | |                 | |        _          |         |       |
   SS_char1, SS_char2, SS_char3, SS_char4, SS_char5, SS_char6, SS_char7, SS_char8, SS_char9,
//  _                                _
// |_  	       _          _          _|
//            |_          _|
   SS_char10, SS_char11, SS_char12, SS_char13 };
//
//  _
//
// Default

////////////////////////////////////////////////////////////////////////////////
//Functionality - Writes output to a 7-segment display
//Parameter: An unsigned character to output
//Returns: None
unsigned char Write7Seg(unsigned char c) {

	// Using the following table:
		//		_A_
		//	F |		| B
		//		_G_
		//	E |		| C
		//		_D_		. DP

	// Match your port and pin numbers:

    static const unsigned char sevenSeg_A		= 2; 		// Pin for segment A
	static const unsigned char sevenSeg_B		= 3; 		// Pin for segment B
	static const unsigned char sevenSeg_C		= 6; 		// Pin for segment C
	static const unsigned char sevenSeg_D		= 5; 		// Pin for segment D
	static const unsigned char sevenSeg_E		= 4; 		// Pin for segment E
	static const unsigned char sevenSeg_F		= 1; 		// Pin for segment F
	static const unsigned char sevenSeg_G		= 0; 		// Pin for segment G
	static const unsigned char sevenSeg_DP		= 7; 		// Pin for segment DP

	// Turns on all segments
	// seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
	//					(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) |	(1<<sevenSeg_DP);

    unsigned char seg_num = 0xFF;

	// Seven Seg character defintions
	switch (c) {
		case SS_0:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F)	;
			break;
		case SS_1:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) ;
			break;
		case SS_2:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_3:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_G) ;
			break;
		case SS_4:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C)	|
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_5:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_6:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_7:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) ;
			break;
		case SS_8:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_9:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_A:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_B:
			seg_num =	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_C:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_D:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_E:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_F:
			seg_num =	(1<<sevenSeg_A)	|
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_DP:
			seg_num =	(1<<sevenSeg_DP);
			break;
		case SS_G:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_H:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_h:
			seg_num =	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_I:
			seg_num =	(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_J:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	;
			break;
		case SS_L:
			seg_num =	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_m:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_N:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_n:
			seg_num =	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_P:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_R:
			seg_num =	(1<<sevenSeg_A)	|
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_r:
			seg_num =	(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_t:
			seg_num =	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_U:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_u:
			seg_num =	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	;
			break;
		case SS_V:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_F) ;
			break;
		case SS_v:
			seg_num =	(1<<sevenSeg_B) |
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_X:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_D) |
								(1<<sevenSeg_G) ;
			break;
		case SS_Y:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_Z:
			seg_num =	(1<<sevenSeg_B) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_lambda:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_char1:
			seg_num =	(1<<sevenSeg_E)	|	(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_char2:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |
								(1<<sevenSeg_G) ;
			break;
		case SS_char3:
			seg_num =	(1<<sevenSeg_B) |	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_F) ;
			break;
		case SS_char4:
			seg_num =	(1<<sevenSeg_B) |
								(1<<sevenSeg_F) ;
			break;
		case SS_char5:
			seg_num =	(1<<sevenSeg_C) |
								(1<<sevenSeg_E)	;
			break;
		case SS_char6:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_D) ;
			break;
		case SS_char7:
			seg_num =	(1<<sevenSeg_C) |
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_char8:
			seg_num =	(1<<sevenSeg_C) |
								(1<<sevenSeg_F) ;
			break;
		case SS_char9:
			seg_num =	(1<<sevenSeg_B) |
								(1<<sevenSeg_E)	;
			break;
		case SS_char10:
			seg_num =	(1<<sevenSeg_A)	|
								(1<<sevenSeg_F) |	(1<<sevenSeg_G) ;
			break;
		case SS_char11:
			seg_num =	(1<<sevenSeg_D) |
								(1<<sevenSeg_E)	|	(1<<sevenSeg_G) ;
			break;
		case SS_char12:
			seg_num =	(1<<sevenSeg_C) |	(1<<sevenSeg_D) |
								(1<<sevenSeg_G) ;
			break;
		case SS_char13:
			seg_num =	(1<<sevenSeg_A)	|	(1<<sevenSeg_B) |
								(1<<sevenSeg_G) ;
			break;

		default:
			seg_num =	(1<<sevenSeg_G) ;
		break;
	}

    return ~seg_num;
}

#endif // SEVEN_SEG_H
