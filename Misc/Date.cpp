struct _Date {
	vector<int> mth, mth_sum;
	_Date() {
		mth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		mth_sum = mth;
		partial_sum(mth.begin(), mth.end(), mth_sum.begin());
	}
};

struct Date: _Date {
	int d, m, y;

	int mdays() { return mth[m] + (m == 2) * leap(); }
	int ydays() { return 365 + leap(); }

	int msum()  { return mth_sum[m-1] + (m > 2) * leap(); }
	int ysum()  { return 365*(y-1) + (y-1)/4 - (y-1)/100 + (y-1)/400; }

	int count() { return (d-1) + msum() + ysum(); }

public:
	Date() : d(1), m(1), y(1) {}
	Date(int d, int m, int y) : d(d), m(m), y(y) {}
	Date(int days) : d(1), m(1), y(1) { advance(days); }

	// se o ano eh bissexto
	bool leap() { return (y%4 == 0 and y%100) or (y%400 == 0); }

	int weekDay() {
		int x = y - (m<3);
		return (x + x/4 - x/100 + x/400 + mth_sum[m-1] + d + 6)%7;
	}

	void advance(int days) {
		days += count();
		d = m = 1, y = 1 + days/366;
		days -= count();
		while(days >= ydays()) days -= ydays(), y++;
		while(days >= mdays()) days -= mdays(), m++;
		d += days;
	}
};