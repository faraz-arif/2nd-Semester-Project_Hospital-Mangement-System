#ifndef STORAGE_H
#define STORAGE_H
template<typename T>
class Storage {
private:
	T data[100];
	int count;
public:
	Storage() : count(0) {
	}

	void add(const T& item) {
		if (count < 100) {
			data[count] = item;
			count++;
		}
		else {
			cout << "Storage Full, Cannot Add more items" << endl;
		}
	}

	T* findByID(int id) {
		for (int i = 0; i < count; i++) {
			if (data[i].getID() == id) {
				return &data[i];
			}
		}
		return nullptr;
	}

	bool removeByID(int id) {
		for (int i = 0; i < count; i++) {
			if (data[i].getID() == id) {
				for (int j = i; j < count - 1; j++) {
					data[j] = data[j + 1];
				}
				count--;
				return true;
			}
		}
		return false;
	}
	int size() const {
		return count;
	}
	T* getAt(int i) {
		if (i >= 0 && i < 100) {
			return &data[i];
		}
		return nullptr;
	}
};
#endif