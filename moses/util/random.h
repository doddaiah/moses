/* random.h --- 
 *
 * Copyright (C) 2010 Novamente LLC
 *
 * Author: Nil Geisweiller
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef _OPENCOG_RANDOM_H
#define _OPENCOG_RANDOM_H

#include <boost/numeric/conversion/cast.hpp>

#include <moses/util/RandGen.h>
#include <moses/util/mt19937ar.h>
#include <moses/util/numeric.h>

/**
 * \file random.h
 *
 * This file contains a collection of random generators based on RandGen
 */

namespace moses3 {
/** \addtogroup grp_cogutil
 *  @{
 */

//! Pick an element of container c randomly, with uniform
//! distribution.  \warning it is assumed that c is non-empty
template<typename C>
const typename C::value_type& rand_element(const C& c, RandGen& rng = randGen())
{
    OC_ASSERT(!c.empty());
    return *std::next(c.begin(), rng.randint(c.size()));
}

//! Pick an element of container c randomly, with uniform
//! distribution, and remove it.  \warning it is assumed that c is
//! non-empty
template<typename C>
typename C::value_type rand_element_erase(C& c, RandGen& rng = randGen())
{
    OC_ASSERT(!c.empty());
    auto it = std::next(c.begin(), rng.randint(c.size()));
    typename C::value_type val = *it;
    c.erase(it);
    return val;
}

//! Return a random number sampled according to a Gaussian distribution.
//! If the number falls out of the range of T then it is automatically
//! truncated.
template<typename T>
T gaussian_rand(T mean, T std_dev, RandGen& rng = randGen())
{
    double val = mean + std_dev *
        std::sqrt(-2 * std::log(rng.randDoubleOneExcluded())) * 
        std::cos(2 * PI * rng.randDoubleOneExcluded());
    T res;
    try {
        res = boost::numeric_cast<T>(val);
    } catch(boost::numeric::positive_overflow&) {
        res = std::numeric_limits<T>::max();
    } catch(boost::numeric::negative_overflow&) {
        res = std::numeric_limits<T>::min();
    }
    return res;
}

//! linear biased random bool, b in [0,1] when b tends to 1 the result
//! tends to be true
static inline bool biased_randbool(float b, RandGen& rng = randGen())
{
    return b > rng.randfloat();
}

/** @}*/
} // ~namespace moses3

#endif // _OPENCOG_RANDOM_H
