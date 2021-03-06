#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <list>
#include <map>
#include <algorithm>
#ifdef _WIN32
#include <filesystem>
#elif __linux__ || __APPLE__
#include <experimental/filesystem>
#endif
#include <sstream>

namespace keilo {
	enum class result_t {
		success = 0,
		fail,
		has_no_value,
		cannot_find,
		already_exist,
		key_overlapped,
		key_not_exist,
		file_not_support
	};
}

#include "instance.hpp"
#include "record.hpp"
#include "table.hpp"
#include "database.hpp"
#include "application.hpp"
#include "json.hpp"
