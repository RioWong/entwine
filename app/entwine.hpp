/******************************************************************************
* Copyright (c) 2016, Connor Manning (connor@hobu.co)
*
* Entwine -- Point cloud indexing
*
* Entwine is available under the terms of the LGPL2 license. See COPYING
* for specific license text and more information.
*
******************************************************************************/

#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "arg-parser.hpp"

#include <entwine/third/arbiter/arbiter.hpp>
#include <entwine/types/dimension.hpp>
#include <entwine/types/reprojection.hpp>
#include <entwine/types/srs.hpp>
#include <entwine/util/json.hpp>
#include <entwine/util/optional.hpp>

namespace entwine
{
namespace app
{

class App
{
public:
    App() : m_json(json::object()) { }
    virtual ~App() { }

    void go(Args args)
    {
        addArgs();
        if (!m_ap.handle(args)) return;
        run();
    }

protected:
    virtual void addArgs() = 0;
    virtual void run() = 0;

    json m_json;
    ArgParser m_ap;

    void addInput(std::string description, bool asDefault = false);
    void addOutput(std::string description, bool asDefault = false);
    void addConfig();
    void addTmp();
    void addSimpleThreads();
    void addReprojection();
    void addNoTrustHeaders();
    void addDeep();
    void addAbsolute();
    void addArbiter();

    void checkEmpty(json j) const
    {
        if (!j.is_null()) throw std::runtime_error("Invalid specification");
    }

    uint64_t extract(json j) const
    {
        return json::parse(j.get<std::string>()).get<uint64_t>();
    }

    std::string yesNo(bool b) const { return b ? "yes" : "no"; }

    std::string getReprojectionString(optional<Reprojection> r);
    std::string getDimensionString(const Schema& schema) const;
    void printProblems(const StringList& warnings, const StringList& errors);
    void printInfo(
        const Schema& schema,
        const Bounds& bounds,
        const Srs& srs,
        uint64_t points,
        const StringList& warnings,
        const StringList& errors);
};

} // namespace app
} // namespace entwine

