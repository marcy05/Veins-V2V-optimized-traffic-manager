/*
	@author Marcello Sgarbi
	@date 07-Feb-2019
*/
/*
***************************************************************************************************************************************************************************
*																			INCLUDE FILES
***************************************************************************************************************************************************************************
*/

#include "Chess.h"


Chess::Chess()
{
	std::bitset<256> aux4chess(m_myChessStr);
	m_myChessBit = aux4chess;
	std::bitset<256> aux4chessMask(m_maskStr);
	m_maskBit = aux4chessMask;

	std::bitset<256> aux4clearMask(m_clearMaskStr);
	m_clearMaskBit = aux4clearMask;

	std::bitset<256> auxE2(m_signalE2Str);
	std::bitset<256> auxE3(m_signalE3Str);
	std::bitset<256> auxE4(m_signalE4Str);
	std::bitset<256> auxE5(m_signalE5Str);
	std::bitset<256> auxE6(m_signalE6Str);
	std::bitset<256> auxE7(m_signalE7Str);

	std::bitset<256> auxN2(m_signalN2Str);
	std::bitset<256> auxN3(m_signalN3Str);
	std::bitset<256> auxN4(m_signalN4Str);
	std::bitset<256> auxN5(m_signalN5Str);
	std::bitset<256> auxN6(m_signalN6Str);
	std::bitset<256> auxN7(m_signalN7Str);

	std::bitset<256> auxW2(m_signalW2Str);
	std::bitset<256> auxW3(m_signalW3Str);
	std::bitset<256> auxW4(m_signalW4Str);
	std::bitset<256> auxW5(m_signalW5Str);
	std::bitset<256> auxW6(m_signalW6Str);
	std::bitset<256> auxW7(m_signalW7Str);

	std::bitset<256> auxS2(m_signalS2Str);
	std::bitset<256> auxS3(m_signalS3Str);
	std::bitset<256> auxS4(m_signalS4Str);
	std::bitset<256> auxS5(m_signalS5Str);
	std::bitset<256> auxS6(m_signalS6Str);
	std::bitset<256> auxS7(m_signalS7Str);

	m_signalE2Bit = auxE2;
	m_signalE3Bit = auxE3;
	m_signalE4Bit = auxE4;
	m_signalE5Bit = auxE5;
	m_signalE6Bit = auxE6;
	m_signalE7Bit = auxE7;

	m_signalN2Bit = auxN2;
	m_signalN3Bit = auxN3;
	m_signalN4Bit = auxN4;
	m_signalN5Bit = auxN5;
	m_signalN6Bit = auxN6;
	m_signalN7Bit = auxN7;

	m_signalW2Bit = auxW2;
	m_signalW3Bit = auxW3;
	m_signalW4Bit = auxW4;
	m_signalW5Bit = auxW5;
	m_signalW6Bit = auxW6;
	m_signalW7Bit = auxW7;

	m_signalS2Bit = auxS2;
	m_signalS3Bit = auxS3;
	m_signalS4Bit = auxS4;
	m_signalS5Bit = auxS5;
	m_signalS6Bit = auxS6;
	m_signalS7Bit = auxS7;
}

Chess::~Chess()
{
}

//Print the intersection in the command window
void Chess::printChess()
{
	
	//Sleep(100);
	//system("cls");

	int counter = 0;
	std::string toPrint;
	std::bitset<256> beforeMasking = m_myChessBit;
	std::bitset<256> mask(m_maskStr);
	std::string maskStr = mask.to_string();
	std::bitset<256> afterMasking = beforeMasking & mask;

	//std::string chess = (~m_myChessBit).to_string();
	std::string chessbeforedel = afterMasking.to_string();
	std::string chess;
	
	for (int i = 0; i < maskStr.length(); ++i) {
		if (maskStr.at(i) == '0') {	chess += " "; }
		else chess += chessbeforedel.at(i);
	}

	for (std::string::iterator it = chess.begin(); it != chess.end(); ++it)
	{
		if (counter < 16) toPrint += *it;
		if (counter == 16) {
			std::cout << toPrint << std::endl;
			//myfile << toPrint;
			counter = 0;
			toPrint = "";
			toPrint = *it;
		}
		counter += 1;
	}
	//print the last iteration
	std::cout << toPrint << std::endl;
		
}


//Print the intersection to the file declared at the beginning of the function
void Chess::printChess2file()
{
	std::ofstream myfile("C:/Users/marce/Desktop/Output_test_chess/OutputTOT.xml", std::ios::app);
	//Sleep(100);
	//system("cls");

	int counter = 0;
	std::string toPrint;
	std::bitset<256> beforeMasking = m_myChessBit;
	std::bitset<256> mask(m_maskStr);
	std::string maskStr = mask.to_string();
	std::bitset<256> afterMasking = beforeMasking & mask;

	//std::string chess = (~m_myChessBit).to_string();
	std::string chessbeforedel = afterMasking.to_string();
	std::string chess;

	for (int i = 0; i < maskStr.length(); ++i) {
		if (maskStr.at(i) == '0') { chess += " "; }
		else chess += chessbeforedel.at(i);
	}

	for (std::string::iterator it = chess.begin(); it != chess.end(); ++it)
	{
		if (counter < 16) toPrint += *it;
		if (counter == 16) {
			myfile << toPrint << std::endl;
			
			counter = 0;
			toPrint = "";
			toPrint = *it;
		}
		counter += 1;
	}
	//print the last iteration
	myfile << toPrint << std::endl;

}

// it clear the setted intersection movement, but it does not clear the vehicles setted
void Chess::clear()
{
	m_myChessBit &= m_clearMaskBit;
	//printChess();
}

// It return integers based on heading
int Chess::checkHeading(double heading)
{
	if (heading > -3.15 && heading < -3.13) return 1; // East
	if (heading > -1.6 && heading < -1.4) return 2; // Nord
	if (heading > -0.1 && heading < 0.1) return 3; // West
	if (heading > 1.4 && heading < 1.6) return 4; // South
	return -1;

}



int Chess::getNVehicle(double heading)
{
	int headResponse = checkHeading(heading);

	return m_numVehicle.at(headResponse - 1);
	/*
	//East
	if (headResponse == 1) { return m_numVehicle.at(headResponse - 1); }
	//Nord
	if (headResponse == 2) { return m_numVehicle.at(headResponse - 1); }
	//West
	if (headResponse == 3) { return m_numVehicle.at(headResponse - 1); }
	//South
	if (headResponse == 4)	{ return m_numVehicle.at(headResponse - 1); }
	*/
}


std::string Chess::findRow(int row)
{
	std::string chess = m_myChessBit.to_string();
	if (row < 16) return chess.substr(row * 16, 16);
	else  return "Error!\nDimentional error: too many rows";
}





void Chess::setCarStart(double heading, int position)
{
	//Heading Research
	//checkHeading:		1->East		2->Nord		3->West		4->South
	int headResponse = checkHeading(heading);

	if (position == 0 || position < 0)
	{
		std::cout << "Error!\n Minumum possible position = 1" << std::endl;
	}
	else {
		//East
		if (headResponse == 1) {
			if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
			else {
				if (m_myChessBit[150 - position] != true) {
					m_myChessBit[150 - position] = true;
					m_numVehicle.at(headResponse - 1) += 1;
				}
			}
		}
		//Nord
		if (headResponse == 2) {
			if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
			else {
				if (m_myChessBit[168 + 16 * (position - 1)] != true) {
					int chessposN = 159 + 9 + 16 * (position - 1);
					m_myChessBit[chessposN] = true;
					m_numVehicle.at(headResponse - 1) += 1;
				}
			}
		}
		//West
		if (headResponse == 3) {
			if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
			else {
				if (m_myChessBit[120 + position] != true) {
					m_myChessBit[120 + position] = true;
					m_numVehicle.at(headResponse - 1) += 1;
				}
			}
		}
		// South
		if (headResponse == 4) {
			if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
			else {
				if (m_myChessBit[102 - 16 * (position - 1)] != true) {
					int chessposS = 95 + 7 - 16 * (position - 1);
					m_myChessBit[chessposS] = true;
					m_numVehicle.at(headResponse - 1) += 1;
				}
			}
		}
	}
}


void Chess::delCarStart(double heading, int position)
{
	//Heading Research
	//checkHeading:		1->East		2->Nord		3->West		4->South
	int headResponse = checkHeading(heading);

	//East
	if (headResponse == 1) {
		if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
		else {
			if (m_myChessBit[150 - position] != false) {
				m_myChessBit[150 - position] = false;
				m_numVehicle.at(headResponse - 1) -= 1;
			}
		}
	}
	//Nord
	if (headResponse == 2) {
		if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
		else {
			if (m_myChessBit[168 + 16 * (position - 1)] != false) {
				int chessposN = 159 + 9 + 16 * (position - 1);
				m_myChessBit[chessposN] = false;
				m_numVehicle.at(headResponse - 1) -= 1;
			}
		}
	}
	//West
	if (headResponse == 3) {
		if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
		else {
			if (m_myChessBit[120 + position] != false) {
				m_myChessBit[120 + position] = false;
				m_numVehicle.at(headResponse - 1) -= 1;
			}
		}
	}
	// South
	if (headResponse == 4) {
		if (position > 6) std::cout << "Error!\nVehicle in direction " << heading << " exceed the queue size" << std::endl;
		else {
			if (m_myChessBit[102 - 16 * (position - 1)] != false) {
				int chessposS = 95 + 7 - 16 * (position - 1);
				m_myChessBit[chessposS] = false;
				m_numVehicle.at(headResponse - 1) -= 1;
			}
		}
	}
}

int Chess::findFirstPosition(double heading)
{
	//Heading Research
	//checkHeading:		1->East		2->Nord		3->West		4->South
	int headResponse = checkHeading(heading);
	int position = 0;
	if (headResponse == 1) {
		for (int i = 1; i <= 6; ++i) {
			if (m_myChessBit[150 - i] == true) {
				position = i;
				break;
			}
		}
		return position;
	}
	if (headResponse == 2) {
		for (int i = 1; i <= 6; ++i) {
			if (m_myChessBit[168 + 16 * (i - 1)] == true) {
				position = i;
				break;
			}
		}
		return position;
	}
	if (headResponse == 3) {
		for (int i = 1; i <= 6; ++i) {
			if (m_myChessBit[120 + i] == true) {
				position = i;
				break;
			}
		}
		return position;
	}
	if (headResponse == 4) {
		for (int i = 1; i <= 6; ++i) {
			if (m_myChessBit[102 - 16 * (i - 1)] == true) {
				position = i;
				break;
			}
		}
		return position;
	}
}

bool Chess::isTheFirst(double heading, int myposition)
{
	int headResponse = checkHeading(heading);
	//East
	if (headResponse == 1) 
	{
		if (myposition == 1) return true;
		if (myposition > 1 && myposition <=6)
		{
			bool toRetunr = false;
			for (int i = 1; i < myposition; ++i) {
				if (m_myChessBit[150 - i] == false) {
					toRetunr = true;
				}
				else { 
					toRetunr = false;
					break;
				}
			}
			return toRetunr;
		}
		else { 
			std::cout << "Invalid check, the position must be <=6 . Current serarch for position = " << myposition << std::endl;
			//throw std::exception();
		}
	}
	//Nord
	if (headResponse == 2) 
	{
		if (myposition == 1) return true;
		if (myposition > 1 && myposition <= 6)
		{
			bool toReturn = false;
			for (int i = 1; i < myposition; ++i) {
				int chessposN = 159 + 9 + 16 * (i - 1);
				if (m_myChessBit[chessposN] == false) {
					toReturn = true;
				}
				else {
					toReturn = false;
					break;
				}
			}
			return toReturn;

		}
	}
	//West
	if (headResponse == 3)
	{
		if (myposition == 1) return true;
		if (myposition > 1 && myposition <= 6)
		{
			bool toRetunr = false;
			for (int i = 1; i < myposition; ++i) {
				if (m_myChessBit[120 + i] == false) {
					toRetunr = true;
				}
				else {
					toRetunr = false;
					break;
				}
			}
			return toRetunr;
		}
		else {
			std::cout << "Invalid check, the position must be <=6 . Current serarch for position = " << myposition << std::endl;
			//throw std::exception();
		}
	}
	//South
	if (headResponse == 4)
	{
		if (myposition == 1) return true;
		if (myposition > 1 && myposition <= 6)
		{
			bool toReturn = false;
			for (int i = 1; i < myposition; ++i) {
				int chessposS = 95 + 7 - 16 * (i - 1);
				if (m_myChessBit[chessposS] == false) {
					toReturn = true;
				}
				else {
					toReturn = false;
					break;
				}
			}
			return toReturn;

		}
	}
}

bool Chess::isPossibleMovement(double heading, int signal, int position)
{
	int headResponse = checkHeading(heading);
	if (headResponse == 1 && isTheFirst(heading, position)) //East
	{
		// turnRight
		if (signal == 2) {
			std::bitset<256>masked = m_myChessBit & m_signalE2Bit;
			// No vehicle on the right
			if (masked.any() == false) {return true;}
			else {return false;}
		}
		// turnLeft
		if (signal == 3) {
			std::bitset<256>masked = m_myChessBit & m_signalE3Bit;
			// No vehicle on the left
			if (masked.any() == false) {return true;}
			else {return false;}
		}

		if (signal == 4) {
			std::bitset<256>masked = m_myChessBit & m_signalE4Bit;
			// No vehicle in front
			if (masked.any() == false) {return true;}
			else {return false;}
		}

		if (signal == 5) {
			std::bitset<256>masked = m_myChessBit & m_signalE5Bit;
			// No vehicle in front AND on the RIGHT
			if (masked.any() == false) {return true;}
			else {return false;}
		}

		if (signal == 6) {
			std::bitset<256>masked = m_myChessBit & m_signalE6Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) {return true;}
			else {return false;}
		}

		if (signal == 7) {
			std::bitset<256>masked = m_myChessBit & m_signalE7Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) {return true;}
			else {return false;}
		}
	}

	if (headResponse == 2 && isTheFirst(heading, position)) //Nord
	{
		// turnRight
		if (signal == 2) {
			std::bitset<256>masked = m_myChessBit & m_signalN2Bit;
			// No vehicle on the right
			if (masked.any() == false) { return true; }
			else { return false; }
		}
		// turnLeft
		if (signal == 3) {
			std::bitset<256>masked = m_myChessBit & m_signalN3Bit;
			// No vehicle on the left
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 4) {
			std::bitset<256>masked = m_myChessBit & m_signalN4Bit;
			// No vehicle in front
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 5) {
			std::bitset<256>masked = m_myChessBit & m_signalN5Bit;
			// No vehicle in front AND on the RIGHT
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 6) {
			std::bitset<256>masked = m_myChessBit & m_signalN6Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 7) {
			std::bitset<256>masked = m_myChessBit & m_signalN7Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) { return true; }
			else { return false; }
		}
	}

	if (headResponse == 3 && isTheFirst(heading, position)) //West
	{
		// turnRight
		if (signal == 2) {
			std::bitset<256>masked = m_myChessBit & m_signalW2Bit;
			// No vehicle on the right
			if (masked.any() == false) { return true; }
			else { return false; }
		}
		// turnLeft
		if (signal == 3) {
			std::bitset<256>masked = m_myChessBit & m_signalW3Bit;
			// No vehicle on the left
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 4) {
			std::bitset<256>masked = m_myChessBit & m_signalW4Bit;
			// No vehicle in front
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 5) {
			std::bitset<256>masked = m_myChessBit & m_signalW5Bit;
			// No vehicle in front AND on the RIGHT
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 6) {
			std::bitset<256>masked = m_myChessBit & m_signalW6Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 7) {
			std::bitset<256>masked = m_myChessBit & m_signalW7Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) { return true; }
			else { return false; }
		}
	}

	if (headResponse == 4 && isTheFirst(heading, position)) //South
	{
		// turnRight
		if (signal == 2) {
			std::bitset<256>masked = m_myChessBit & m_signalS2Bit;
			// No vehicle on the right
			if (masked.any() == false) { return true; }
			else { return false; }
		}
		// turnLeft
		if (signal == 3) {
			std::bitset<256>masked = m_myChessBit & m_signalS3Bit;
			// No vehicle on the left
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 4) {
			std::bitset<256>masked = m_myChessBit & m_signalS4Bit;
			// No vehicle in front
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 5) {
			std::bitset<256>masked = m_myChessBit & m_signalS5Bit;
			// No vehicle in front AND on the RIGHT
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 6) {
			std::bitset<256>masked = m_myChessBit & m_signalS6Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) { return true; }
			else { return false; }
		}

		if (signal == 7) {
			std::bitset<256>masked = m_myChessBit & m_signalS7Bit;
			// No vehicle in front AND on the LEFT
			if (masked.any() == false) { return true; }
			else { return false; }
		}
	}
}



bool Chess::checkAndSetSignal(double heading, int signal, int position)
{
	int headResponse = checkHeading(heading);

	if (headResponse == 1) //East
	{
		//Stop
		if (signal == 1)
		{
			return true;
		}
		//TR
		if (signal == 2) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalE2Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//TL
		if (signal == 3) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalE3Bit;
				//printChess();
				return true;
				
			}
			else { 
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St
		if (signal == 4) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalE4Bit;
				//printChess();
				return true;
				
			}
			else { 
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TR
		if (signal == 5) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalE5Bit;
				//printChess();
				return true;
				
			}
			else { 
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TL
		if (signal == 6) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalE6Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TL + TR
		if (signal == 7) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalE7Bit;
				//printChess();
				return true;
				
			}
			else { 
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
	}

	if (headResponse == 2) //Nord
	{
		//Stop
		if (signal == 1)
		{
			return true;
		}
		//TR
		if (signal == 2) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalN2Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//TL
		if (signal == 3) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalN3Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St
		if (signal == 4) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalN4Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TR
		if (signal == 5) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalN5Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TL
		if (signal == 6) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalN6Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TL + TR
		if (signal == 7) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) { 
				m_myChessBit |= m_signalN7Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
	}

	if (headResponse == 3) //West
	{
		//Stop
		if (signal == 1)
		{
			return true;
		}
		//TR
		if (signal == 2) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalW2Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//TL
		if (signal == 3) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalW3Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St
		if (signal == 4) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalW4Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TR
		if (signal == 5) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalW5Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TL
		if (signal == 6) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) { 
				m_myChessBit |= m_signalW6Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St + TL + TR
		if (signal == 7) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalW7Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
	}

	if (headResponse == 4) //South
	{
		//Stop
		if (signal == 1)
		{
			return true;
		}
		//TR
		if (signal == 2) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) { 
				m_myChessBit |= m_signalS2Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//TL
		if (signal == 3) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalS3Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
		//St
		if (signal == 4) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalS4Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl; 
				return false;
			}
		}
		//St + TR
		if (signal == 5) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalS5Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl; 
				return false;
			}
		}
		//St + TL
		if (signal == 6) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) { 
				m_myChessBit |= m_signalS6Bit;
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl; 
				return false;
			}
		}
		//St + TL + TR
		if (signal == 7) {
			//No vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == true) {
				m_myChessBit |= m_signalS7Bit; 
				//printChess();
				return true;
				
			}
			else {
				std::cout << "Already present a vehicle in " << heading << " with signal " << signal << "\nOr NOT the first vehicle" << std::endl;
				return false;
			}
		}
	}

}


void Chess::checkAndRemoveSignal(double heading, int signal, int position) 
{
	int headResponse = checkHeading(heading);
	if (headResponse == 1) //East
	{
		//TR
		if (signal == 2) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalE2Bit;
				m_myChessBit ^= m_signalE2Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//TL
		if (signal == 3) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalE3Bit;
				m_myChessBit ^= m_signalE3Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St
		if (signal == 4) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalE4Bit;
				m_myChessBit ^= m_signalE4Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TR
		if (signal == 5) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalE5Bit;
				m_myChessBit ^= m_signalE5Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL
		if (signal == 6) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalE6Bit;
				m_myChessBit ^= m_signalE6Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL + TR
		if (signal == 7) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalE7Bit;
				m_myChessBit ^= m_signalE7Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}
	}

	if (headResponse == 2) //Nord
	{
		//TR
		if (signal == 2) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalN2Bit;
				m_myChessBit ^= m_signalN2Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//TL
		if (signal == 3) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalN3Bit;
				m_myChessBit ^= m_signalN3Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St
		if (signal == 4) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalN4Bit;
				m_myChessBit ^= m_signalN4Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TR
		if (signal == 5) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalN5Bit;
				m_myChessBit ^= m_signalN5Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL
		if (signal == 6) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalN6Bit;
				m_myChessBit ^= m_signalN6Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL + TR
		if (signal == 7) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalN7Bit;
				m_myChessBit ^= m_signalN7Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}
	}

	if (headResponse == 3) //West
	{
		//TR
		if (signal == 2) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalW2Bit;
				m_myChessBit ^= m_signalW2Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//TL
		if (signal == 3) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalW3Bit;
				m_myChessBit ^= m_signalW3Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St
		if (signal == 4) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalW4Bit;
				m_myChessBit ^= m_signalW4Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TR
		if (signal == 5) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalW5Bit;
				m_myChessBit ^= m_signalW5Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL
		if (signal == 6) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalW6Bit;
				m_myChessBit ^= m_signalW6Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL + TR
		if (signal == 7) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalW7Bit;
				m_myChessBit ^= m_signalW7Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}
	}

	if (headResponse == 4) //South
	{
		//TR
		if (signal == 2) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalS2Bit;
				m_myChessBit ^= m_signalS2Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//TL
		if (signal == 3) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalS3Bit;
				m_myChessBit ^= m_signalS3Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St
		if (signal == 4) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalS4Bit;
				m_myChessBit ^= m_signalS4Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TR
		if (signal == 5) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalS5Bit;
				m_myChessBit ^= m_signalS5Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL
		if (signal == 6) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalS6Bit;
				m_myChessBit ^= m_signalS6Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}

		//St + TL + TR
		if (signal == 7) {
			//Vehicle conflicting
			if (isPossibleMovement(heading, signal, position) == false) {
				std::bitset<256> masked = m_myChessBit & m_signalS7Bit;
				m_myChessBit ^= m_signalS7Bit;
				//printChess();
			}
			else { std::cout << "No vehicle conflicting in direction " << heading << " with signal " << signal << std::endl; }
		}
	}

}



/*
Mask
0000000111000000
0000000111000000
0000000111000000
0000000111000000
0000000111000000
0000000111000000
0111111111111111
0111111111111111
0111111111111111
0000000111000000
0000000111000000
0000000111000000
0000000111000000
0000000111000000
0000000111000000
0000000000000000
*/

/*
0111111100111111011111110011111101111111001111110111111100111111011111110011111101111111001111110000000000111111000000000000000001111110000000000111111001111111011111100111111101111110011111110111111001111111011111100111111101111110011111110000000000000000
Clear Mask
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0000000000111111
0000000000000000
0111111000000000
0111111001111111
0111111001111111
0111111001111111
0111111001111111
0111111001111111
0111111001111111
0000000000000000


Clear W
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0111111100111111
0111111100000000
0111111101111111
0111111001111111
0111111001111111
0111111001111111
0111111001111111
0111111001111111
0111111001111111
0000000000000000
*/

/*
std::string SignalE2Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalE3Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000001000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalE4Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalE5Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000111111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalE6Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111111000000000000001000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalE7Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000111111111000000000000001000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";

std::string SignalN2Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalN3Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000001000000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalN4Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalN5Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalN6Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000011000000000000001011111110000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalN7Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111100000000000000011000000000000001011111110000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";

std::string SignalW2Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalW3Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000001000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalW4Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalW5Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";
std::string SignalW6Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000001000000000000001111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalW7Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000001000000000000001111111110000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000000000000";

std::string SignalS2Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalS3Str = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111100000000000000001000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalS4Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalS5Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalS6Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000111111101000000000000001100000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
std::string SignalS7Str = "0000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000111111101000000000000001100000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
*/

/*
E2
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

E3
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000001000000
0000000010000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

E4
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111111000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

E5
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0111111111000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

E6
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111111000000
0000000010000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

E7
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0111111111000000
0000000010000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

*/

/*
N2
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111100000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

N3
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000100000000
0000000010000000
0000000001111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

N4
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

N5
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

N6
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000100000000
0000000110000000
0000000101111111
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

N7
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111100000000
0000000110000000
0000000101111111
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

*/

/*
W2
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

W3
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000010000000
0000000100000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

W4
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000111111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

W5
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000111111111
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

W6
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000010000000
0000000111111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

W7
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000010000000
0000000111111111
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

*/

/*
S2
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000001111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000


S3
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111100000000
0000000010000000
0000000001000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000


S4
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

S5
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

S6
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0111111101000000
0000000011000000
0000000001000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000

S7
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0111111101000000
0000000011000000
0000000001111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000


*/

/*
East mask == E7
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0111111111000000
0000000010000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

Nord mask == N7
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0111111100000000
0000000110000000
0000000101111111
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

West mask == W7
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000010000000
0000000111111111
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000100000000
0000000000000000

South mask == S7
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0000000001000000
0111111101000000
0000000011000000
0000000001111111
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
*/









