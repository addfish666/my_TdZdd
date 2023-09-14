/*
 * Copyright (c) 2014 Hiroaki Iwashita
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <iostream>
#include <vector>

#include <tdzdd/DdSpec.hpp>
#include "Board.hpp"

class NumlinZdd: public tdzdd::HybridDdSpec<NumlinZdd,uint16_t,uint8_t,2> {
    Board const& quiz;
    int const max_blank;
    int const m, n, top_level;

public:
    /**
     * Constructor.
     * @param quiz matrix of number pairs.
     * @param max_blank maximum number of unused boxes.
     */
    NumlinZdd(Board const& quiz, int max_blank = -1) :
                    quiz(quiz),
                    max_blank(max_blank),
                    m(quiz.rows),
                    n(quiz.cols),
                    top_level(m * (n - 1)) {
        setArraySize(quiz.cols);
    }

    /**
     * Gets a root configuration.
     * @param blank_count total count of blank cells.
     * @param mate mate array.
     * @return root level.
     */
    int getRoot(S_State& blank_count, A_State* mate) const;

    /**
     * Gets a child configuration.
     * @param blank_count total count of blank cells.
     * @param mate mate array.
     * @param level decision level.
     * @param take 1 to take the edge; 0 otherwise.
     * @return next decision level.
     */
    int getChild(S_State& blank_count, A_State* mate, int level, int take) const;

    /**
     * Prints a state.
     * @param os output stream.
     * @param blank_count total count of blank cells.
     * @param mate mate array.
     */
    void printState(std::ostream& os, S_State const& blank_count,
            A_State const* mate) const;
};
