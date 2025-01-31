/*
* Author: Dante Trisciuzzi (Triscuit2311)
* Created: 2025-01-31
* License: MIT License (see LICENSE file)
*/

#pragma once
#include "pch.h"

#define USE_CONSOLE true
#define USE_OBF false
#ifdef xorstr_
#define x_x_(v) xorstr_(v)
#else
#define x_x_(v) (v)
#endif

namespace logger
{
	class
	{
	private:
		HANDLE console_hdl;
		WORD console_saved_attrs;
		bool console_use_ansi = false;

		bool enable_virtual_terminal_processing()
		{
			console_hdl = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD mode;
			if (!GetConsoleMode(console_hdl, &mode))
			{
				return false;
			}
			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			return SetConsoleMode(console_hdl, mode);
		}

		template <typename... Args>
		void log_with_color(const wchar_t* prefix, WORD color, const wchar_t* format, Args... args)
		{
			if constexpr (!USE_CONSOLE)
			{
				return;
			}

			if (console_use_ansi)
			{
				const wchar_t* colorCode = get_color_code(color);
				wprintf(x_x_(L"%s %s %c "), colorCode, prefix, 16);
				wprintf(x_x_(L"\x1B[0m"));
				wprintf(format, args...);
				wprintf(x_x_(L"\n"));
			}
			else
			{
				SetConsoleTextAttribute(console_hdl, color);
				wprintf(x_x_(L"%s "), prefix);
				SetConsoleTextAttribute(console_hdl, console_saved_attrs);
				wprintf(format, args...);
				wprintf(x_x_(L"\n"));
			}
		}

		static const wchar_t* get_color_code(WORD color)
		{
			switch (color)
			{
			case FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY:
				return L"\x1B[1;93m"; // yellow
			case FOREGROUND_GREEN | FOREGROUND_INTENSITY:
				return L"\x1B[1;92m"; // bright green
			case FOREGROUND_RED | FOREGROUND_INTENSITY:
				return L"\x1B[1;91m"; // bright red
			case FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY:
				return L"\x1B[1;96m"; // bright cyan
			default:
				return L"\x1B[0;37m"; // white
			}
		}

		std::wstring s2ws(const std::string& str)
		{
			return std::wstring(str.begin(), str.end());
		}

	public:
		template <typename... Args>
		void log(const wchar_t* format, Args... args)
		{
			log_with_color(x_x_(L"+"), 1, format, args...);
		}

		template <typename... Args>
		void log(const char* format, Args... args)
		{
			log_with_color(x_x_(L"+"), 1, s2ws(format).c_str(), args...);
		}

		template <typename... Args>
		void log(const std::string& format, Args... args)
		{
			log_with_color(x_x_(L"+"), 1, s2ws(format).c_str(), args...);
		}

		template <typename... Args>
		void log(const std::wstring& format, Args... args)
		{
			log_with_color(x_x_(L"+"), 1, format.c_str(), args...);
		}

		template <typename... Args>
		void info(const wchar_t* format, Args... args)
		{
			log_with_color(x_x_(L"i"), FOREGROUND_GREEN | FOREGROUND_INTENSITY, format, args...);
		}

		template <typename... Args>
		void info(const char* format, Args... args)
		{
			log_with_color(x_x_(L"i"), FOREGROUND_GREEN | FOREGROUND_INTENSITY, s2ws(format).c_str(), args...);
		}

		template <typename... Args>
		void info(const std::string& format, Args... args)
		{
			log_with_color(x_x_(L"i"), FOREGROUND_GREEN | FOREGROUND_INTENSITY, s2ws(format).c_str(), args...);
		}

		template <typename... Args>
		void info(const std::wstring& format, Args... args)
		{
			log_with_color(x_x_(L"i"), FOREGROUND_GREEN | FOREGROUND_INTENSITY, format.c_str(), args...);
		}

		template <typename... Args>
		void err(const wchar_t* format, Args... args)
		{
			log_with_color(x_x_(L"x"), FOREGROUND_RED | FOREGROUND_INTENSITY, format, args...);
		}

		template <typename... Args>
		void err(const char* format, Args... args)
		{
			log_with_color(x_x_(L"x"), FOREGROUND_RED | FOREGROUND_INTENSITY, s2ws(format).c_str(), args...);
		}

		template <typename... Args>
		void err(const std::string& format, Args... args)
		{
			log_with_color(x_x_(L"x"), FOREGROUND_RED | FOREGROUND_INTENSITY, s2ws(format).c_str(), args...);
		}

		template <typename... Args>
		void err(const std::wstring& format, Args... args)
		{
			log_with_color(x_x_(L"x"), FOREGROUND_RED | FOREGROUND_INTENSITY, format.c_str(), args...);
		}

		template <typename... Args>
		void warn(const wchar_t* format, Args... args)
		{
			log_with_color(x_x_(L"!"), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, format, args...);
		}

		template <typename... Args>
		void warn(const char* format, Args... args)
		{
			log_with_color(x_x_(L"!"), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, s2ws(format).c_str(),
				args...);
		}

		template <typename... Args>
		void warn(const std::string& format, Args... args)
		{
			log_with_color(x_x_(L"!"), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, s2ws(format).c_str(),
				args...);
		}

		template <typename... Args>
		void warn(const std::wstring& format, Args... args)
		{
			log_with_color(x_x_(L"!"), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, format.c_str(),
				args...);
		}

		template <typename... Args>
		void special(const wchar_t* format, Args... args)
		{
			log_with_color(x_x_(L"~"), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, format, args...);
		}

		template <typename... Args>
		void special(const char* format, Args... args)
		{
			log_with_color(x_x_(L"~"), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, s2ws(format).c_str(),
				args...);
		}

		template <typename... Args>
		void special(const std::string& format, Args... args)
		{
			log_with_color(x_x_(L"~"), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, s2ws(format).c_str(),
				args...);
		}

		template <typename... Args>
		void special(const std::wstring& format, Args... args)
		{
			log_with_color(x_x_(L"~"), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, format.c_str(),
				args...);
		}

		void init()
		{
			if constexpr (USE_CONSOLE)
			{
				AllocConsole();
				freopen_s((FILE**)stdout, x_x_("CONOUT$"), x_x_("w, ccs=UNICODE"), stdout);
				console_use_ansi = enable_virtual_terminal_processing();
				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
				GetConsoleScreenBufferInfo(console_hdl, &consoleInfo);
				console_saved_attrs = consoleInfo.wAttributes;
				log(x_x_(L"Console Allocated"));
			}
		}

		void free()
		{
			if constexpr (USE_CONSOLE)
			{
				log(x_x_(L"Console Freed"));
				FreeConsole();
			}
		}

		void set_title()
		{
		}
	} static inline con;
}
