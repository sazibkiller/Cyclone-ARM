# Cyclone-ARM

Cyclone এর ARM সংস্করণ — মোবাইল (Android/Termux) এর জন্য অপ্টিমাইজ করা।
- ARM NEON SIMD সাপোর্ট
- মোবাইলে সরাসরি কম্পাইল ও রান করা যাবে
- Samsung A54 CPU এর জন্য টিউন করা

## Install & Run
```bash
pkg install clang git make
git clone https://github.com/sazibkiller/Cyclone-ARM.git
cd Cyclone-ARM
make
./cyclone_arm
