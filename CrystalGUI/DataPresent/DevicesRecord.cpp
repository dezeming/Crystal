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

#include "CrystalAlgrithm/Utility/cpu_Common.hpp"

namespace CrystalGUI {

void showCudaDevicesInfo(void) {

	CrystalAlgrithm::printCudaDevice();

	std::vector<CrystalAlgrithm::CudaDeviceProperty> cudadevices;
	CrystalAlgrithm::getCudaDevice(cudadevices);

	for (int i = 0; i < cudadevices.size(); i++) {
		m_GuiStatus.setDataChanged( ("GPU[" + std::to_string(i) + "]").c_str(), "GPU name", cudadevices[i].GPU_name.c_str());
		m_GuiStatus.setDataChanged( ("GPU[" + std::to_string(i) + "]").c_str(), "Compute capability", cudadevices[i].Compute_capability.c_str());
		m_GuiStatus.setDataChanged( ("GPU[" + std::to_string(i) + "]").c_str(), "Clock rate", cudadevices[i].Clock_rate.c_str());
		m_GuiStatus.setDataChanged( ("GPU[" + std::to_string(i) + "]").c_str(), "Total global memory", cudadevices[i].Total_global_memory.c_str());
		m_GuiStatus.setDataChanged( ("GPU[" + std::to_string(i) + "]").c_str(), "Total constant memory", cudadevices[i].Total_constant_memory.c_str());
		m_GuiStatus.setDataChanged( ("GPU[" + std::to_string(i) + "]").c_str(), "Multiprocessor count", cudadevices[i].Multiprocessor_count.c_str());
	}
	


}



}




