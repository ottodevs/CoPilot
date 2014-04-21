#ifndef STR_ENUM_H
#define STR_ENUM_H

#include <unordered_set>
//usage: std::unordered_set<StrEnum,StrEnum::StrHash> sem({"one","two","three"});

class StrEnum {
public:
	StrEnum(const std::string& ext_name)
		: ptr(new EnumBase(ext_name, nextIndex())) { }

	std::string toString() const { return ptr->name; }
private:
	static inline int nextIndex() {
		static int firstIdx = 0;
		return firstIdx++;
	}
	struct EnumBase {
		EnumBase(const std::string& ext_name, int ext_idx)
			: name(ext_name), index(ext_idx) { }
		const std::string name;
		const int index;
	};
	const EnumBase *ptr;
public:
	friend bool operator<(const StrEnum& x, const StrEnum& y) {
		return x.ptr->index < y.ptr->index;
	}
	friend bool operator==(const StrEnum& x, const StrEnum& y) { return x.ptr==y.ptr; }
	friend bool operator!=(const StrEnum& x, const StrEnum& y) { return !(x==y); }

	class StrHash {
	public:
		std::size_t operator()(const StrEnum& sem) const {
			return static_cast<std::size_t>(djb2(sem.toString()));
		}
	private:
		static unsigned long djb2(const std::string& str) {		//by Daniel J. Bernstein
			unsigned long hash=5381;
			for(std::size_t idx=0;idx<str.size();++idx) {
				hash=((hash<<5)+hash)^str[idx];				//hash*33 ^ c (another version: hash*33+c)
			}
			return hash;
		}
		static unsigned long sdbm(const std::string& str) {
			unsigned long hash=0;
			for(std::size_t idx=0;idx<str.size();++idx) {
				hash=str[idx] + (hash<<6)+(hash<<16)-hash;	//hash*65599 + c
			}
			return hash;
		}
		static unsigned long joat(const std::string& str) {		//Jenkins's one-at-a-time hash by Bob Jenkins
			unsigned long hash=0;
			for(std::size_t idx=0;idx<str.size();++idx) {
				hash+=str[idx];
				hash+=(hash<<10);
				hash^=(hash>>6);
			}
			hash+=(hash<<3);
			hash^=(hash>>11);
			hash+=(hash<<15);
			return hash;
		}
	};
};

inline std::ostream& operator<< (std::ostream& o, const StrEnum& s) {
	return o<<s.toString();
}

#endif // STR_ENUM_H
