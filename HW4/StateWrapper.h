#pragma once
template<typename state>
struct state_wrapper_t {
	state_wrapper_t() {}
	state_wrapper_t(state a, int b, int c, int d) : s(a), g(b), h(c), rank(d) {}
	state s;
	int g;
	int h;
	int rank;
	inline void operator=(const state_wrapper_t<state>& r)
	{
		s = r.s;
		g = r.g;
		h = r.h;
		rank = r.rank;
	}
	inline bool operator==(const state_wrapper_t<state>& rhs) const
	{
		return s == rhs.s;
	}

};

