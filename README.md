# Robo-Con2025
2025年でETロボコンを行った際のプログラム

## 各ファイルの構成について
```bash
src/
├── app/                                ← フレームワーク/起動層
│   ├── Tracer.cpp
│   ├── Tracer.h
│   └── main_task.cpp                   ← main()やETロボコン起動点
│
├── entities/                           ← エンティティ層（純粋な抽象）
│   ├── ColorEvaluationStrategy.h
│   └── EdgeFollowingStrategy.h
│
├── usecase/                            ← ユースケース層
│   └── TracerController.h
│
├── interface_adapters/                ← インターフェースアダプタ層
│   ├── color_eval/
│   │   ├── ReflectiveBrightnessEval.h
│   │   ├── RGBEval.h
│   │   └── HSVEval.h
│   └── edge_following/
│       ├── LeftEdgeStrategy.h
│       └── RightEdgeStrategy.h
│
└── drivers/                            ← ドライバ（センサ・ハード抽象）
    ├── ColorSensor.h
    └── WheelController.h
```


