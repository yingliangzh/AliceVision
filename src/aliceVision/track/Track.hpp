// This file is part of the AliceVision project.
// Copyright (c) 2016 AliceVision contributors.
// Copyright (c) 2012 openMVG contributors.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/config.hpp>
#include <aliceVision/feature/imageDescriberCommon.hpp>
#include <aliceVision/matching/IndMatch.hpp>
#include <aliceVision/stl/FlatMap.hpp>
#include <aliceVision/stl/FlatSet.hpp>

#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <memory>

namespace aliceVision {
namespace track {

using namespace aliceVision::matching;

/**
 * @brief A Track is a feature visible accross multiple views.
 * Tracks are generated by the fusion of all matches accross all images.
 */
struct Track
{
  /// Data structure to store a track: collection of {ViewId, FeatureId}
  typedef stl::flat_map<std::size_t, std::size_t> FeatureIdPerView;

  Track() {}

  /// Descriptor type
  feature::EImageDescriberType descType = feature::EImageDescriberType::UNINITIALIZED;
  /// Collection of matched features between views: {ViewId, FeatureId}
  FeatureIdPerView featPerView;
};

/// A track is a collection of {trackId, Track}
typedef stl::flat_map<std::size_t, Track> TracksMap;
typedef std::vector<std::size_t> TrackIdSet;

/**
 * @brief Data structure that contains for each features of each view, its corresponding cell positions for each level of the pyramid, i.e.
 * for each view:
 *   each feature is mapped N times (N=depth of the pyramid)
 *      each times it contains the absolute position P of the cell in the corresponding pyramid level
 *
 * FeatsPyramidPerView contains map<viewId, map<trackId*N, pyramidIndex>>
 *
 * Cell position:
 * Consider the set of all cells of all pyramids, there are M = \sum_{l=1...N} K_l^2 cells with K_l = 2^l and l=1...N
 * We enumerate the cells starting from the first pyramid l=1 (so that they have position from 0 to 3 (ie K^2 - 1))
 * and we go on for increasing values of l so that e.g. the first cell of the pyramid at l=2 has position K^2, the second K^2 + 1 etc...
 * So in general the i-th cell of the pyramid at level l has position P= \sum_{j=1...l-1} K_j^2 + i
 */
typedef stl::flat_map<std::size_t, stl::flat_map<std::size_t, std::size_t> > TracksPyramidPerView;

/**
 * @brief TracksPerView is a list of visible track ids for each view.
 * TracksPerView contains <viewId, vector<trackId>>
 */
typedef stl::flat_map<std::size_t, TrackIdSet > TracksPerView;


} // namespace track
} // namespace aliceVision
