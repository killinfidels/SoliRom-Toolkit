#pragma once

namespace SoliRom
{
	class Log
	{
	public:
		//Enables console colors, already run in the entrypoint
		static void Init();

		enum class Severity
		{
			Info,
			Trace,
			Warn,
			Error,
			Fatal
		};

		enum class Logger
		{
			Core,
			Client
		};

		//TODO: SET OWN COLORS

		static void WriteToConsole(Logger lgr, Severity svy, const char* str, ...);

	private:

	};
}

//engine log macros
//GREEN
#define SR_CORE_TRACE(...)   ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Core, SoliRom::Log::Severity::Trace, __VA_ARGS__)
//WHITE
#define SR_CORE_INFO(...)    ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Core, SoliRom::Log::Severity::Info, __VA_ARGS__)
//YELLOW
#define SR_CORE_WARN(...)    ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Core, SoliRom::Log::Severity::Warn, __VA_ARGS__)
//DARK RED
#define SR_CORE_ERROR(...)   ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Core, SoliRom::Log::Severity::Error, __VA_ARGS__)
//VIBRANT RED
#define SR_CORE_FATAL(...)   ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Core, SoliRom::Log::Severity::Fatal, __VA_ARGS__)
							
//app log macros								
//GREEN
#define SR_TRACE(...)        ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Client, SoliRom::Log::Severity::Trace, __VA_ARGS__)
//WHITE
#define SR_INFO(...)         ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Client, SoliRom::Log::Severity::Info, __VA_ARGS__)
//YELLOW
#define SR_WARN(...)         ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Client, SoliRom::Log::Severity::Warn, __VA_ARGS__)
//DARK RED
#define SR_ERROR(...)        ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Client, SoliRom::Log::Severity::Error, __VA_ARGS__)
//VIBRANT RED
#define SR_FATAL(...)        ::SoliRom::Log::WriteToConsole(SoliRom::Log::Logger::Client, SoliRom::Log::Severity::Fatal, __VA_ARGS__)