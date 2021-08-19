#include <bits/stdc++.h>
using namespace std;

struct WriteCache {
	static constexpr int buf_size = 1<<12;
	static constexpr int size_mask = buf_size - 1;

	int last = 0;
	char buf[buf_size];

	void flush() {
		fwrite(buf, 1, last, stdout);
		last = 0;
	}

    template<typename T, enable_if_t<is_same_v<T, char>, bool> = true>
	void print(T c) {
		// DBG((int)c);
		buf[last++] = c;
		if (last == buf_size) flush();
	}

	template<typename T, enable_if_t<is_convertible_v<T, string_view>, bool> = true>
	void print(T const& s_raw) {
		auto s = string_view(s_raw);
		int len = s.size();

		if (last + len >= buf_size) {
			int old_last = last;
			int to_end = buf_size - last;
			copy(s.begin(), s.begin() + to_end, buf + last);
			last = buf_size;
			flush();
			int i = to_end;
			for (; i + buf_size < len; i += buf_size) {
				copy(s.begin() + i, s.begin() + i + buf_size, buf);
				last = buf_size;
				flush();
			}
			copy(s.begin() + i, s.end(), buf);
			last = (old_last + len) & size_mask;
		}
		else {
			copy(s.begin(), s.end(), buf + last);
			last += len;
		}
	}

	template<typename T, enable_if_t<is_integral_v<T> && !is_same_v<T, char>, bool> = true>
	void print(T x) {
		static char int_buf[50];
		auto* beg = end(int_buf);

		bool neg = x < 0;
		if (neg) x = -x;

		do {
			--beg;
			*beg = x%10 + '0';
			x /= 10;
		} while (x);

		if (neg) {
			--beg;
			*beg = '-';
		}
		auto sv = string_view(beg, end(int_buf) - beg);
		print(sv);
	}

	template<typename T, typename... Args>
	void operator()(T const& a, Args const& ...args) {
		print<T>(a);
		if constexpr (sizeof...(args) >= 1) {
			(*this)(args...);
		}
	}

	~WriteCache() {
		if (last) flush();
	}
} print;


// usage
// print("asdiuahsi ", 3, ' ', __int128(5), " ", string("aa"), '\n');