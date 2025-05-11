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


