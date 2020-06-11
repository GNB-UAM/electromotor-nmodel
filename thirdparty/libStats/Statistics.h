/*************************************************************

 Copyright (c) 2012, 2013, Fernando Herrero Carrón
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

#ifndef STATISTICS_STATISTICS_H_
#define STATISTICS_STATISTICS_H_

#include <list>
#include <memory>
#include <string>

#include <boost/multi_array.hpp>

#include "MatrixStreamer.h"

#include <H5Cpp.h>

namespace libStats
{

/**
 * @author Fernando Herrero Carrón
 * @date 10/01/2013
 *
 * Statistics holds a pointer to an HDF5 file and is responsible for its management.
 *
 * ### YAML configuration options: ###
 * @todo Fill this
 */

class Statistics
{
public:
	typedef std::shared_ptr<Statistics> SharedPtr;
	typedef std::unique_ptr<Statistics> UniquePtr;

	Statistics(std::string filename, std::string group);
	virtual ~Statistics();

	void write(std::string const &name, unsigned int i);
	void write(std::string const &name, float v);

	MatrixStreamer::SharedPtr get_matrix_streamer(hsize_t dims[2], std::string name);

	void dump();

protected:
	boost::multi_array<float, 2> _robot_traces;

	std::list<MatrixStreamer::SharedPtr> _streamers;

	const std::string _filename;

	H5::H5File _hdf5_file;
	H5::Group _group;
};
}

#endif /* STATISTICS_STATISTICS_H_ */
