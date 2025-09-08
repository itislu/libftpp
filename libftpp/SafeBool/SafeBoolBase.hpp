#pragma once

namespace ft {
namespace _safe_bool {

class SafeBoolBase {
public:
	typedef void (SafeBoolBase::*safe_bool_t)() const;
	void this_type_does_not_support_comparisons() const;

protected:
	SafeBoolBase();
	~SafeBoolBase();

private:
	SafeBoolBase(const SafeBoolBase& /*unused*/);
	SafeBoolBase& operator=(const SafeBoolBase& /*unused*/);
};

} // namespace _safe_bool
} // namespace ft
