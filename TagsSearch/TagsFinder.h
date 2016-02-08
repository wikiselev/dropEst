#pragma once

#include "FilesProcessor.h"
#include "SpacerFinder.h"
#include "Counters/TrimsCounter.h"

#include <string>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/property_tree/ptree.hpp>

//class SpacerFinder;

namespace TestTagsSearch
{
	struct test1;
	struct test2;
}


class TagsFinder
{
	friend struct TestTagsSearch::test1;
	friend struct TestTagsSearch::test2;

private:
	typedef std::string::size_type len_t;

	long max_reads;
	unsigned min_align_len;
	std::string poly_a;

	SpacerFinder spacer_finder;
	TrimsCounter trims_counter;

private:
	static std::string reverse_complement(const std::string &s);

	static bool read_blocks(FilesProcessor &files_processor, long total_reads_read,
							std::string &out_1_line_2, std::string &out_2_line_2, std::string &out_2_line_3,
							std::string &out_2_line_4);

	std::string results_to_string(long total_reads_read) const;
	len_t get_trim_position(len_t spacer_pos, const std::string &r1_line, const std::string &r2_line);
	std::string process_lines(long total_reads_read, const std::string &r1_line2,
					   std::string &r2_line2, const std::string &r2_line3, std::string &r2_line4);

public:
	TagsFinder()
	{}

	TagsFinder(const SpacerFinder &spacer_finder, const boost::property_tree::ptree &config);

	void run(const std::string &r1_filename, const std::string &r2_filename, const std::string &base_name);
};