#pragma once

#include <DataStreams/IBlockInputStream.h>
#include <Interpreters/Context.h>

#include <Storages/RabbitMQ/StorageRabbitMQ.h>
#include <Storages/RabbitMQ/ReadBufferFromRabbitMQConsumer.h>


namespace DB
{

    class RabbitMQBlockInputStream : public IBlockInputStream
    {
    public:
        RabbitMQBlockInputStream(StorageRabbitMQ & storage_, const Context & context_, const Names & columns);
        ~RabbitMQBlockInputStream() override;

        String getName() const override { return storage.getName(); }
        Block getHeader() const override;

        void readPrefixImpl() override;
        Block readImpl() override;
        void readSuffixImpl() override;

        void commit();

    private:
        StorageRabbitMQ & storage;
        Context context;
        Names column_names;

        ConsumerBufferPtr buffer;
    };
}