# Дослідження обмежень ресурсів у середовищі Docker
## Встановлення Docker
```bash
sudo apt update
sudo apt install -y docker.io
sudo systemctl enable docker
sudo systemctl start docker
sudo usermod -aG docker vlad
```
Після цього потрібно перезавантажити систему
### Створення Dockerfile:
```Dockerfile
FROM ubuntu:22.04

RUN apt update && \
    apt install -y linux-tools-common linux-tools-generic

CMD ["bash"]

```
### Побудова Docker-образу
```bash
cd pr3
docker build -t pr3env .
```
### Запуск контейнера з ресурсними лімітами
```bash
docker run -it --name pr3container --ulimit nofile=2048:4096 pr3env
```

## Завдання 3.1 Дослідження ulimit
![image](https://github.com/user-attachments/assets/3d5c061c-2126-4586-ba1b-06a803f9b3b4)
![image](https://github.com/user-attachments/assets/f082fd76-68f6-4661-bb4b-2229c91ba20e)
![image](https://github.com/user-attachments/assets/776e526a-0cc2-436d-8bcf-66828059d172)
![image](https://github.com/user-attachments/assets/a4cca625-9725-4938-9eee-1f1c21985de7)
![image](https://github.com/user-attachments/assets/fe29247e-6da0-4422-bccd-4c39064b7396)
![image](https://github.com/user-attachments/assets/27537952-27bb-48fb-a0c4-cecdd1ac3f1c)
![image](https://github.com/user-attachments/assets/336f4dc5-4f86-45bb-a423-9566bf87746d)
![image](https://github.com/user-attachments/assets/32e30fd8-afcf-4b14-9699-e4a17afdcaed)

### Для перевірки з root правами
```bash
apt install -y sudo
sudo -i
```
![image](https://github.com/user-attachments/assets/b7d52d7d-78c2-41c7-9d98-1a4f103524e8)

### Перевірка з root правами
![image](https://github.com/user-attachments/assets/ced79532-51cc-4d17-9e87-b27e4b144f0f)

## Завдання 3.2
При спробі виконати 
```bash
perf stat ls
```
видається попередження, 
```
perf command not found for kernel 6.8.0-59
```
Це означає, що утиліта встановлена, проте не сумісна з ядром, для виправлення необхідно встановити відповідну версію linux-tools
```bash
apt install -y linux-tools-6.8.0-59-generic

```
![image](https://github.com/user-attachments/assets/895efd65-847c-4d4d-8dbe-8fa173117956)
Це повідомлення означає, що користувач не має прав для запуску perf, бо ця утиліта потребує доступу до низькорівневих подій ядра.
Щоб виправити це, запустимо контейнер з розширеними привілеями
```bash
docker run --rm -it --privileged pr3env
```
#### Результат виконання 
```bash
perf stat ls
```
![image](https://github.com/user-attachments/assets/731e80d6-30dd-4e4b-b66c-7dfd281deb83)

##### При написанні докерфайлу не передбачив завантаження редактора nano та компілятора gcc тому дозавантажую походу
Створимо файл infinite.c
```c
#include <stdio.h>
int main(){
    while(1);
    return 0;
}
```
Скомпілюємо
```bash
gcc -o infinite infinite.c
```
Запустимо з perf
```bash
perf stat ./infinite
```
Цього разу контейнер був запущений без вказаних лімітних обмежень, тому програма триватиме вічно, поки ми не зупинимо процес, після примусового завершення процесу отримуємо:
![image](https://github.com/user-attachments/assets/f6d8e98c-95dc-4ead-ac37-c2501f9e7743)

## Завдання 3.3
```bash
ulimit -f 1  # ліміт 1 блок = 512 байт
```

Скомпілюємо
```bash
gcc -Wall -o dice dice.c
```

### Результат
![image](https://github.com/user-attachments/assets/a81ea0d5-dbf5-42a9-9c4a-3d30d791f401)

### Вміст dice.log
![image](https://github.com/user-attachments/assets/5b348ec1-6ff4-45a8-ab89-11e452e3b244)

## Завдання 3.4
```bash
ulimit -t 1 # max CPU time
```

Скомпілюємо
```bash
gcc -Wall -o lottery lottery.c
```
### Результат
![image](https://github.com/user-attachments/assets/20614a2d-df23-4907-9e84-c60203035137)

## Завдання 3.5
### Створимо маленький файл
```bash
echo "Test" > source.txt
```
Скомпілюємо та запустимо
```bash
gcc -Wall -o copy copy.c
./copy source.txt dest.txt
```
Все спрацювало
Тепер перевіримо обробку на перебільшення розміру файлу
Встановимо ліміт
```bash
ulimit -f 1
```
### Результат
![image](https://github.com/user-attachments/assets/8f3a095e-b885-4717-82fe-3bdb40b30a8f)

## Завдання 3.6
```bash
ulimit -s 64 # stack size
```

Скомпілюємо
```bash
gcc -Wall -o stack stack.c
```

### Результат
![image](https://github.com/user-attachments/assets/c51e0a7e-3e12-49ed-8abf-47a586e73ee0)

### Для порівняння результат без лімітів
![image](https://github.com/user-attachments/assets/d1ac8aff-ad60-45fc-8f5f-9ea8c1322e03)

## Завдання 3.7
```bash
ulimit -u 10 # max processes
```
### Скомпілюємо
```bash
gcc -Wall -o processes processes.c
```

### Результат
![image](https://github.com/user-attachments/assets/34cc2304-e10f-43a6-be52-5b06bfdf0905)











