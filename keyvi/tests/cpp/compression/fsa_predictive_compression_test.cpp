//
// keyvi - A key value store.
//
// Copyright 2015 Hendrik Muhs<hendrik.muhs@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/*
 * fsa_predictive_compression_test.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: hendrik
 */


#include <boost/test/unit_test.hpp>
#include "dictionary/testing/temp_dictionary.h"
#include "compression/fsa_predictive_compression.h"

namespace keyvi {
namespace compression {

BOOST_AUTO_TEST_SUITE( FSAPredictiveCompressionTests )

BOOST_AUTO_TEST_CASE( CompressAndUncompress ) {
  std::vector<std::pair<std::string, std::string>> bigrams = { { "ht", "tp://" }, {
      "tt", "ps://" }, {"//", "www."}, {"th", "e"}, };

  dictionary::testing::TempDictionary dictionary(bigrams);

  auto compressor = FsaPredictiveCompression(dictionary.GetFsa());

  std::string input = "http://www.the-test.com";
  std::string output = compressor.Compress(input);
  std::string uncompressed = compressor.Uncompress(output);
  BOOST_CHECK_EQUAL(2 + 13, output.size());
  BOOST_CHECK_EQUAL(input, uncompressed);

  input = "aa";
  output = compressor.Compress(input);
  BOOST_CHECK_EQUAL(input, compressor.Uncompress(output));

  input = std::string("null\0http://www.\0-byte.com", 26);
  output = compressor.Compress(input);
  uncompressed = compressor.Uncompress(output);
  BOOST_CHECK_EQUAL(input, uncompressed);
  BOOST_CHECK_EQUAL(26, input.size());
  BOOST_CHECK_EQUAL(26, uncompressed.size());
}

BOOST_AUTO_TEST_SUITE_END()

}
}

