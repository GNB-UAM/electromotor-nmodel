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

#ifndef MATRIXSTREAMER_H_
#define MATRIXSTREAMER_H_

#include <boost/multi_array.hpp>
#include <memory>

#include <H5Cpp.h>

namespace libStats
{

/**
 * @author Fernando Herrero Carrón
 * @date 14/02/2013 (Happy V- day!!)
 */

class MatrixStreamer
{
public:
	typedef std::unique_ptr<MatrixStreamer> UniquePtr;
	typedef std::shared_ptr<MatrixStreamer> SharedPtr;

	MatrixStreamer(hsize_t dims[2], H5::DataSet dataset);

	virtual ~MatrixStreamer();

	MatrixStreamer &operator<<(float x);
//	MatrixStreamer &operator<<(Vector2D v);

	void dump();

protected:
	boost::multi_array<float, 1> _array;
	boost::multi_array<float, 1>::iterator _iterator;

#ifndef NDEBUG
	unsigned int _counter = 0;
#endif

	H5::DataSet _dataset;
};

}

#endif /* MATRIXSTREAMER_H_ */
