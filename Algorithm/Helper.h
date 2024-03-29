#pragma once
#include <utility>

#ifndef HELPER_H
#define HELPER_H

static int min(int x, int y, int z) { return std::min(std::min(x, y), z); }

#endif