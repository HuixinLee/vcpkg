#pragma once

#include <vcpkg/build.h>
#include <vcpkg/dependencies.h>
#include <vcpkg/statusparagraphs.h>
#include <vcpkg/vcpkgcmdarguments.h>
#include <vcpkg/vcpkgpaths.h>

#include <array>

namespace vcpkg::Commands
{
    using CommandTypeA = void (*)(const VcpkgCmdArguments& args,
                                  const VcpkgPaths& paths,
                                  const Triplet& default_triplet);
    using CommandTypeB = void (*)(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    using CommandTypeC = void (*)(const VcpkgCmdArguments& args);

    namespace BuildExternal
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths, const Triplet& default_triplet);
    }

    namespace CI
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths, const Triplet& default_triplet);
    }

    namespace Env
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths, const Triplet& default_triplet);
    }

    namespace Create
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Edit
    {
        extern const CommandStructure COMMAND_STRUCTURE;
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace DependInfo
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Search
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace List
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Owns
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Cache
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Import
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Integrate
    {
        extern const char* const INTEGRATE_COMMAND_HELPSTRING;
        extern const CommandStructure COMMAND_STRUCTURE;

        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace PortsDiff
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Autocomplete
    {
        void perform_and_exit(const VcpkgCmdArguments& args, const VcpkgPaths& paths);
    }

    namespace Version
    {
        const std::string& version();
        void warn_if_vcpkg_version_mismatch(const VcpkgPaths& paths);
        void perform_and_exit(const VcpkgCmdArguments& args);
    }

    namespace Contact
    {
        const std::string& email();
        void perform_and_exit(const VcpkgCmdArguments& args);
    }

    namespace Hash
    {
        void perform_and_exit(const VcpkgCmdArguments& args);
    }

    template<class T>
    struct PackageNameAndFunction
    {
        std::string name;
        T function;
    };

    Span<const PackageNameAndFunction<CommandTypeA>> get_available_commands_type_a();
    Span<const PackageNameAndFunction<CommandTypeB>> get_available_commands_type_b();
    Span<const PackageNameAndFunction<CommandTypeC>> get_available_commands_type_c();

    template<typename T>
    T find(const std::string& command_name, const std::vector<PackageNameAndFunction<T>> available_commands)
    {
        for (const PackageNameAndFunction<T>& cmd : available_commands)
        {
            if (cmd.name == command_name)
            {
                return cmd.function;
            }
        }

        // not found
        return nullptr;
    }
}
