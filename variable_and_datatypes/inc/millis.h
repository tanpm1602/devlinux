#ifndef _MILLIS_H_
#define _MILLIS_H_

// Trả về số mili-giây kể từ lần gọi đầu tiên (giống Arduino millis()).
unsigned long long millis(void);

// Nếu muốn lấy mili-giây kể từ epoch (1970-01-01), dùng hàm này.
unsigned long long epoch_millis(void);

#endif
