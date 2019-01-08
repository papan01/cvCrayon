#ifndef CVCRAYON_IMGPROC_MAT_H
#define CVCRAYON_IMGPROC_MAT_H

#include <memory>
#include "../utils/debugutils.h"

namespace imgproc
{
	template <typename T>
	class Mat
	{
	public:
		Mat() {}
		Mat(int rows, int cols, int channels) :
			rows_(rows), cols_(cols), channels_(channels),
			data_{ new T[rows * cols * channels], std::default_delete<T[]>() } {}
		virtual ~Mat() {};

		T &at(int r, int c, int ch = 0) {
			ASSERT(r < rows_);
			ASSERT(c < cols_);
			ASSERT(ch < channels_);
			return ptr(r)[c * channels_ + ch];
		}

		const T &at(int r, int c, int ch = 0) const {
			ASSERT(r < rows_);
			ASSERT(c < cols_);
			ASSERT(ch < channels_);
			return ptr(r)[c * channels_ + ch];
		}

		T *ptr(int r = 0)
		{
			return data_.get() + r * cols_ * channels_;
		}

		const T *ptr(int r = 0) const
		{
			return data_.get() + r * cols_ * channels_;
		}

		T *ptr(int r, int c)
		{
			return data_.get() + (r * cols_ + c) * channels_;
		}

		const T *ptr(int r, int c) const
		{
			return data_.get() + (r * cols_ + c) * channels_;
		}

		Mat<T> clone() const {
			Mat<T> res(rows_, cols_, channels_);
			memcpy(res.ptr(0), this->ptr(0), sizeof(T) * rows_ * cols_ * channels_);
			return res;
		}

		int height() const { return rows_; }
		int width() const { return cols_; }
		int rows() const { return rows_; }
		int cols() const { return cols_; }
		int channels() const { return channels_; }
		int size() const { return rows_ * cols_; }
		int pixels() const { return rows_ * cols_; }


	protected:
		int rows_, cols_;
		int channels_;
		std::shared_ptr<T> data_;
	};

	using Matf = Mat<float>;
	using Matuc = Mat<unsigned char>;
}

#endif // !CVCRAYON_IMGPROC_MAT_H

