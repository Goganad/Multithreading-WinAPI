#ifndef MULTITHREADING_WINAPI_FILESTITCHER_H
#define MULTITHREADING_WINAPI_FILESTITCHER_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>

using namespace std;

class FileStitcher {
public:
    template<typename T>
    static void sort(T *array, size_t size) noexcept {
        if (size > 1) {
            size_t const left_size = size / 2;
            size_t const right_size = size - left_size;

            FileStitcher::sort(&array[0], left_size);
            FileStitcher::sort(&array[left_size], right_size);

            size_t lidx = 0, ridx = left_size, idx = 0;
            unique_ptr<T[]> tmp_array(new T[size]);

            while (lidx < left_size || ridx < size) {
                if (array[lidx] < array[ridx]) {
                    tmp_array[idx++] = move(array[lidx]);
                    lidx++;
                } else {
                    tmp_array[idx++] = move(array[ridx]);
                    ridx++;
                }

                if (lidx == left_size) {
                    copy(make_move_iterator(&array[ridx]), make_move_iterator(&array[size]), &tmp_array[idx]);
                    break;
                }
                if (ridx == size) {
                    copy(make_move_iterator(&array[lidx]), make_move_iterator(&array[left_size]), &tmp_array[idx]);
                    break;
                }
            }

            copy(make_move_iterator(&tmp_array[0]), make_move_iterator(&tmp_array[size]), array);
        }
    }
};


#endif
