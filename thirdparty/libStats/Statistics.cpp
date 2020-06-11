/*************************************************************

 Copyright (c) 2012, Fernando Herrero Carrón 
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.  
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following
 disclaimer in the documentation and/or other materials provided
 with the distribution. 
 * Neither the name of the author nor the names of his contributors
 may be used to endorse or promote products derived from this
 software without specific prior written permission. 

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *************************************************************/

#include "Statistics.h"

#include <iostream>

using namespace std;
using namespace H5;

namespace libStats
{

Statistics::Statistics(std::string filename, std::string group) :
		_filename(filename)
{
	_hdf5_file.openFile(_filename.c_str(), H5F_ACC_CREAT | H5F_ACC_RDWR);

	_group =_hdf5_file.createGroup(group.c_str());
}

Statistics::~Statistics()
{
}

void Statistics::dump()
{
	try
	{
		for(auto streamer : _streamers)
		{
			streamer->dump();
		}
	}
	catch(Exception const &e)
	{
		e.printErrorStack();
	}
}

void Statistics::write(std::string const &name, float v)
{
	DSetCreatPropList plist;
	plist.setLayout(H5D_COMPACT);

	DataSpace space;

	auto dataset =_group.createDataSet(name.c_str(), PredType::NATIVE_FLOAT, space, plist);

	dataset.write(&v, PredType::NATIVE_FLOAT);
}

void Statistics::write(std::string const &name, unsigned int i)
{
	DSetCreatPropList plist;
	plist.setLayout(H5D_COMPACT);

	DataSpace space;

	auto dataset =_group.createDataSet(name.c_str(), PredType::NATIVE_UINT, space, plist);

	dataset.write(&i, PredType::NATIVE_UINT);
}

MatrixStreamer::SharedPtr Statistics::get_matrix_streamer(hsize_t dims[2], std::string name)
{
	try
	{
		float fillvalue = 0;
		DSetCreatPropList plist;
		plist.setFillValue(PredType::NATIVE_FLOAT, &fillvalue);

		DataSpace fspace(2, dims);
		auto dataset = _group.createDataSet(name.c_str(), PredType::NATIVE_FLOAT, fspace, plist);

		MatrixStreamer::SharedPtr result = make_shared<MatrixStreamer>(dims, dataset);

		_streamers.push_back(result);

		return result;
	}
	catch(H5::Exception const &e)
	{
		cerr << "Problem creating dataset " << name << " within data file " << _filename << '\n';

		e.printErrorStack();

		throw;
	}
}

}
