#ifndef NonCopyable_h
#define NonCopyable_h

namespace simpleNet {
class NonCopyable {
public:
	NonCopyable() = default;

private:
	NonCopyable(const NonCopyable&) = delete;
	void operator=(const NonCopyable&) = delete;
};

} // namespace

#endif