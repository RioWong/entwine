if (NOT WIN32)
    find_package(Backtrace)
    if (${Backtrace_FOUND})
        set(BACKTRACE_DEFS ENTWINE_HAVE_BACKTRACE)
    endif()
endif()
