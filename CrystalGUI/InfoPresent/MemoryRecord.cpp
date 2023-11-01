/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef CRYSTAL_Using_Shared_Lib
#undef _EXPORTING
#endif

#include"CrystalGUI/utility/Status.hpp"

#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib") 

namespace CrystalGUI {

void showMemoryInfo(void) {

	//  SIZE_T PeakWorkingSetSize; //Peak memory usage
	//  SIZE_T WorkingSetSize; //Memory usage
	//  SIZE_T PagefileUsage; //Virtual Memory Usage
	//  SIZE_T PeakPagefileUsage; //Peak virtual memory usage

	EmptyWorkingSet(GetCurrentProcess());

	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));

	m_GuiStatus.setDataChanged("Memory Use", "WorkingSetSize", QString::number(pmc.WorkingSetSize / 1000.f / 1000.f), "M");
	m_GuiStatus.setDataChanged("Memory Use", "PeakWorkingSetSize", QString::number(pmc.PeakWorkingSetSize / 1000.f / 1000.f), "M");
	m_GuiStatus.setDataChanged("Memory Use", "PagefileUsage", QString::number(pmc.PagefileUsage / 1000.f / 1000.f), "M");
	m_GuiStatus.setDataChanged("Memory Use", "PeakPagefileUsage", QString::number(pmc.PeakPagefileUsage / 1000.f / 1000.f), "M");

}


}
