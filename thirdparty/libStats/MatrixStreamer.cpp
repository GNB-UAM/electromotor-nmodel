/*************************************************************

 Copyright (c) 2013, Fernando Herrero Carrón 
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

#include "MatrixStreamer.h"

#include <config.h>

using namespace std;
using namespace H5;

namespace libStats
{

/*
 * Use dims[0] + 1 (max_iterations + 1) because robots write their position at
 * creation time before the simulation begins.
 */

MatrixStreamer::MatrixStreamer(hsize_t dims[2], H5::DataSet dataset) : _array(boost::extents[(dims[0] + 1) * dims[1] * 2]), _dataset(dataset)
{
	_iterator = begin(_array);
}

MatrixStreamer::~MatrixStreamer()
{

}

MatrixStreamer &MatrixStreamer::operator<<(float x)
{
	*_iterator = x;

	_iterator++;

	return *this;
}

/*
MatrixStreamer &MatrixStreamer::operator<<(Vector2D v)
{
	*this << v.x;
	*this << v.y;

	return *this;
}
*/

void MatrixStreamer::dump()
{
	_dataset.write(_array.data(), PredType::NATIVE_FLOAT);
}
}
